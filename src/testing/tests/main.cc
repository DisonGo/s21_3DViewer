#include <gtest/gtest.h>

#include <iostream>

#include "Parsers/OBJParser.h"

s21::OBJParser parser;
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
std::string path_inside_src = "/testing/tests/test_resource/";
std::string test_resources_path = TOSTRING(MYPATH) + path_inside_src;

TEST(viewer_3d, parser_first_test) {
  auto result = parser.ParseRaw(test_resources_path + "empty.jenya");
  EXPECT_EQ(result.obj.vertices.size(), 0);
}

TEST(viewer_3d, parser_second_test) {
  auto result = parser.ParseRaw(test_resources_path + "cube.jenya");
  EXPECT_TRUE(result.objects.size() == 1);
  EXPECT_EQ(result.obj.vertices.size(), 24);
  EXPECT_EQ(result.obj.faces.size(), 12);
  EXPECT_STREQ(result.objects.back().name.c_str(), "Box");
}

TEST(viewer_3d, parser_vertices_test) {
  auto result = parser.ParseRaw(test_resources_path + "cube.jenya");

  static const std::vector<s21::Vertex> vertices = {
      {0.5, 0.5, 0.5},    {0.5, 0.5, -0.5},  {0.5, -0.5, 0.5},
      {0.5, -0.5, -0.5},  {-0.5, 0.5, -0.5}, {-0.5, 0.5, 0.5},
      {-0.5, -0.5, -0.5}, {-0.5, -0.5, 0.5}, {-0.5, 0.5, -0.5},
      {0.5, 0.5, -0.5},   {-0.5, 0.5, 0.5},  {0.5, 0.5, 0.5},
      {-0.5, -0.5, 0.5},  {0.5, -0.5, 0.5},  {-0.5, -0.5, -0.5},
      {0.5, -0.5, -0.5},  {-0.5, 0.5, 0.5},  {0.5, 0.5, 0.5},
      {-0.5, -0.5, 0.5},  {0.5, -0.5, 0.5},  {0.5, 0.5, -0.5},
      {-0.5, 0.5, -0.5},  {0.5, -0.5, -0.5}, {-0.5, -0.5, -0.5}};
  EXPECT_TRUE(result.obj.vertices.size() > 0);
  auto& obj = result.obj;
  for (size_t i = 0; i < obj.vertices.size(); i++) {
    EXPECT_TRUE(obj.vertices[i] == vertices[i]);
  }
}

TEST(viewer_3d, parser_indices_test) {
  auto result = parser.ParseRaw(test_resources_path + "cube.jenya");

  static const std::vector<s21::Face> indices = {
      {{{1, 0, 0}, {3, 0, 0}, {2, 0, 0}}},
      {{{3, 0, 0}, {4, 0, 0}, {2, 0, 0}}},
      {{{5, 0, 0}, {7, 0, 0}, {6, 0, 0}}},
      {{{7, 0, 0}, {8, 0, 0}, {6, 0, 0}}},
      {{{9, 0, 0}, {11, 0, 0}, {10, 0, 0}}},
      {{{11, 0, 0}, {12, 0, 0}, {10, 0, 0}}},
      {{{13, 0, 0}, {15, 0, 0}, {14, 0, 0}}},
      {{{15, 0, 0}, {16, 0, 0}, {14, 0, 0}}},
      {{{17, 0, 0}, {19, 0, 0}, {18, 0, 0}}},
      {{{19, 0, 0}, {20, 0, 0}, {18, 0, 0}}},
      {{{21, 0, 0}, {23, 0, 0}, {22, 0, 0}}},
      {{{23, 0, 0}, {24, 0, 0}, {22, 0, 0}}}};
  auto& obj = result.obj;
  EXPECT_EQ(obj.faces.size(), indices.size());
  for (size_t i = 0; i < obj.faces.size(); ++i) {
    for (size_t j = 0; j < obj.faces.at(i).indices.size(); ++j) {
      auto& source_FV = indices.at(i).indices.at(j);
      auto& parsed_FV = obj.faces.at(i).indices.at(j);
      EXPECT_EQ(source_FV.v_index - 1, parsed_FV.v_index);
    }
  }
}

TEST(viewer_3d, some_group_names) {
  std::vector<s21::OBJ> result =
      parser.Parse(test_resources_path + "third.jenya");

  EXPECT_EQ(result.size(), 2);
  EXPECT_STREQ(result[0].name.c_str(), "Box");
  EXPECT_STREQ(result[1].name.c_str(), "Group");

  EXPECT_EQ(result[0].vertices.size(), 4);
  EXPECT_EQ(result[0].faces.size(), 2);

  EXPECT_EQ(result[1].vertices.size(), 3);
  EXPECT_EQ(result[1].faces.size(), 1);
}

TEST(viewer_3d, no_files) {
  std::vector<s21::OBJ> result = parser.Parse(test_resources_path + "NOFILE");
  EXPECT_TRUE(result.empty());
}

int main() {
  s21::Logger::DeactivateLogLevel(s21::Logger::LogLevel::kBasic);
  s21::Logger::DeactivateLogLevel(s21::Logger::LogLevel::kInfo);
  s21::Logger::DeactivateLogLevel(s21::Logger::LogLevel::kWarning);
  s21::Logger::DeactivateLogLevel(s21::Logger::LogLevel::kError);
  s21::Logger::DeactivateLogLevel(s21::Logger::LogLevel::kCritical);
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
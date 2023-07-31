#include <iostream>
#include <gtest/gtest.h>

#include "Parsers/OBJParser.h"

s21::OBJParser parser;

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
std::string path_inside_src = "/testing/tests/test_resource/";
std::string test_resources_path = TOSTRING(MYPATH) + path_inside_src;

TEST(viewer_3d, parser_first_test) {
  std::vector<s21::OBJ> result = parser.Parse(test_resources_path + "1.obj");
  EXPECT_EQ(result.back().faces.size(), 1000);
}

TEST(viewer_3d, parser_second_test) {
  std::vector<s21::OBJ> result = parser.Parse(test_resources_path + "2.obj");
  EXPECT_EQ(result.back().vertices.size(), 24);
  EXPECT_EQ(result.back().faces.size(), 12);
  EXPECT_STREQ(result.back().name.c_str(), "Box");
}

TEST(viewer_3d, parser_vertices_test) {
  std::vector<s21::OBJ> result = parser.Parse(test_resources_path + "2.obj");

  static const std::vector<std::vector<float>> points = {
    { 2, 2, 2 },
    { 2, 2, -2 },
    { 2, -2, 2 },
    { 2, -2, -2},
    { -2, 2, -2 },
    { -2, 2, 2 },
    { -2, -2, -2},
    { -2, -2, 2 },
    { -2, 2, -2 },
    { 2, 2, -2 },
    { -2, 2, 2  },
    { 2, 2, 2  },
    { -2, -2, 2 },
    { 2, -2, 2 },
    { -2 ,-2, -2},
    { 2, -2, -2},
    { -2, 2, 2  },
    { 2, 2, 2  },
    { -2, -2, 2 },
    { 2, -2, 2 },
    { 2, 2, -2 },
    { -2, 2, -2 },
    { 2, -2, -2},
    { -2, -2, -2} 
  };

  for (size_t i = 0; i < result.back().vertices.size(); i++) {
    EXPECT_FLOAT_EQ(result.back().vertices[i].x, points[i][0]);
    EXPECT_FLOAT_EQ(result.back().vertices[i].y, points[i][1]);
    EXPECT_FLOAT_EQ(result.back().vertices[i].z, points[i][2]);
  }

}

TEST(viewer_3d, parser_indices_test) {
  std::vector<s21::OBJ> result = parser.Parse(test_resources_path + "2.obj");

  static const std::vector<std::vector<int>> indices = {
    {1, 3, 2},
    {3, 4, 2},
    {5, 7, 6},
    {7, 8, 6},
    {9, 11, 10},
    {11, 12, 10},
    {13, 15, 14},
    {15, 16, 14},
    {17, 19, 18},
    {19, 20, 18},
    {21, 23, 22},
    {23, 24, 22}
  };
  size_t counter = 0;
  for (size_t i = 0; i < result.back().faces.size(); i++) {
    for (size_t j = 0; j < result.back().faces[i].indices.size(); j++) {
      EXPECT_EQ(result.back().faces[i].indices[j].v_index, (indices[i][counter++] - 1));
    }
    counter = 0;
  }
}

TEST(viewer_3d, some_group_names) {
  std::vector<s21::OBJ> result = parser.Parse(test_resources_path + "3.obj");

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
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
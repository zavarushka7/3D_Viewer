#include <gtest/gtest.h>

#include <cmath>

#include "../Model/Model.h"

using namespace s21;

// ------------------------- ThreeDPoint Tests ---------------------------

TEST(ThreeDPointTest, Equality) {
  ThreeDPoint p1(1.0f, 2.0f, 3.0f);
  ThreeDPoint p2(1.0f, 2.0f, 3.0f);
  ThreeDPoint p3(1.1f, 2.0f, 3.0f);

  EXPECT_TRUE(p1 == p2);
  EXPECT_FALSE(p1 == p3);
}

TEST(ThreeDPointTest, Comparison) {
  ThreeDPoint p1(1.0f, 2.0f, 3.0f);
  ThreeDPoint p2(1.1f, 2.0f, 3.0f);
  ThreeDPoint p3(1.0f, 3.0f, 3.0f);

  EXPECT_TRUE(p1 < p2);
  EXPECT_TRUE(p1 < p3);
  EXPECT_TRUE(p2 > p1);
}

TEST(ThreeDPointTest, LessOperatorFullCoverage) {
  ThreeDPoint p1(1.0f, 2.0f, 3.0f);
  ThreeDPoint p2(2.0f, 1.0f, 1.0f);
  EXPECT_TRUE(p1 < p2);
  EXPECT_FALSE(p2 < p1);

  ThreeDPoint p3(1.0f, 1.0f, 3.0f);
  ThreeDPoint p4(1.0f, 2.0f, 1.0f);
  EXPECT_TRUE(p3 < p4);
  EXPECT_FALSE(p4 < p3);

  ThreeDPoint p5(1.0f, 2.0f, 3.0f);
  ThreeDPoint p6(1.0f, 2.0f, 4.0f);
  EXPECT_TRUE(p5 < p6);
  EXPECT_FALSE(p6 < p5);

  ThreeDPoint p7(1.0f, 2.0f, 3.0f);
  ThreeDPoint p8(1.0f, 2.0f, 3.0f);
  EXPECT_FALSE(p7 < p8);
  EXPECT_FALSE(p8 < p7);
}

TEST(ThreeDPointTest, GreaterOperatorFullCoverage) {
  ThreeDPoint p1(2.0f, 1.0f, 1.0f);
  ThreeDPoint p2(1.0f, 2.0f, 3.0f);
  EXPECT_TRUE(p1 > p2);
  EXPECT_FALSE(p2 > p1);

  ThreeDPoint p3(1.0f, 2.0f, 1.0f);
  ThreeDPoint p4(1.0f, 1.0f, 3.0f);
  EXPECT_TRUE(p3 > p4);
  EXPECT_FALSE(p4 > p3);

  ThreeDPoint p5(1.0f, 2.0f, 4.0f);
  ThreeDPoint p6(1.0f, 2.0f, 3.0f);
  EXPECT_TRUE(p5 > p6);
  EXPECT_FALSE(p6 > p5);

  ThreeDPoint p7(1.0f, 2.0f, 3.0f);
  ThreeDPoint p8(1.0f, 2.0f, 3.0f);
  EXPECT_FALSE(p7 > p8);
  EXPECT_FALSE(p8 > p7);
}

// -------------------------- Vertex Tests ------------------------------

TEST(VertexTest, PositionSetGet) {
  Vertex v({1.0f, 2.0f, 3.0f});
  EXPECT_FLOAT_EQ(v.GetPosition().x, 1.0f);

  v.setPosition({4.0f, 5.0f, 6.0f});
  EXPECT_EQ(v.GetPosition(), ThreeDPoint(4.0f, 5.0f, 6.0f));
}

TEST(VertexTest, GreaterOperator) {
  Vertex v1(ThreeDPoint(1.0f, 2.0f, 3.0f));
  Vertex v2(ThreeDPoint(4.0f, 5.0f, 6.0f));
  Vertex v3(ThreeDPoint(1.0f, 2.0f, 3.0f));

  EXPECT_TRUE(v2 > v1);
  EXPECT_FALSE(v1 > v2);
  EXPECT_FALSE(v1 > v3);
  EXPECT_FALSE(v3 > v1);
}

// --------------------------- Edge Tests -------------------------------

TEST(EdgeTest, GreaterOperator) {
  Vertex v1({1.0f, 0.0f, 0.0f});
  Vertex v2({2.0f, 0.0f, 0.0f});
  Vertex v3({3.0f, 0.0f, 0.0f});
  Vertex v4({1.0f, 1.0f, 0.0f});

  Edge e1, e2, e3, e4, e5;
  e1.setBegin(&v1);
  e1.setEnd(&v2);
  e2.setBegin(&v2);
  e2.setEnd(&v3);
  e3.setBegin(&v1);
  e3.setEnd(&v3);
  e4.setBegin(&v1);
  e4.setEnd(&v4);
  e5.setBegin(&v1);
  e5.setEnd(&v2);

  EXPECT_TRUE(e2 > e1);
  EXPECT_FALSE(e1 > e2);
  EXPECT_TRUE(e3 > e1);
  EXPECT_FALSE(e1 > e3);
  EXPECT_FALSE(e4 > e1);
  EXPECT_TRUE(e1 > e4);
  EXPECT_FALSE(e1 > e5);
  EXPECT_FALSE(e5 > e1);

  Vertex v5({4.0f, 0.0f, 0.0f});
  Vertex v6({0.0f, 0.0f, 0.0f});
  Edge e6, e7;
  e6.setBegin(&v5);
  e6.setEnd(&v6);
  e7.setBegin(&v1);
  e7.setEnd(&v3);

  EXPECT_TRUE(e6 > e7);
}

TEST(EdgeTest, VertexLinking) {
  Vertex v1({0, 0, 0}), v2({1, 1, 1});
  Edge e;
  e.setBegin(&v1);
  e.setEnd(&v2);

  EXPECT_EQ(e.GetBegin(), &v1);
  EXPECT_EQ(e.GetEnd(), &v2);
}

TEST(EdgeTest, Comparison) {
  Vertex v1({0, 0, 0}), v2({1, 0, 0}), v3({0, 1, 0});
  Edge e1, e2, e3;
  e1.setBegin(&v1);
  e1.setEnd(&v2);
  e2.setBegin(&v1);
  e2.setEnd(&v3);
  e3.setBegin(&v2);
  e3.setEnd(&v3);

  EXPECT_TRUE(e1 < e3);
  EXPECT_TRUE(e2 < e3);
  EXPECT_FALSE(e1 == e2);
}

// ---------------------- TransformMatrix Tests --------------------------

TEST(TransformMatrixTest, Multiplication) {
  TransformMatrix m1;
  m1.setMatrixElement(0, 0, 2.0f);
  TransformMatrix m2;
  m2.setMatrixElement(0, 0, 3.0f);

  TransformMatrix res = m1 * m2;
  EXPECT_FLOAT_EQ(res.getMatrixElement(0, 0), 6.0f);
}

TEST(TransformMatrixTest, PointTransformation) {
  TransformMatrix m;
  m.setMatrixElement(0, 3, 5.0f);

  ThreeDPoint p(1.0f, 2.0f, 3.0f);
  ThreeDPoint res = m.TransformPoint(p);

  EXPECT_FLOAT_EQ(res.x, 6.0f);
  EXPECT_FLOAT_EQ(res.y, 2.0f);
}

// ------------------ TransformMatrixBuilder Tests -----------------------

TEST(TransformMatrixBuilderTest, TranslationMatrix) {
  auto m = TransformMatrixBuilder::CreateMoveMatrix(2.0, 3.0, 4.0);
  ThreeDPoint p(1.0f, 1.0f, 1.0f);
  ThreeDPoint res = m.TransformPoint(p);

  EXPECT_FLOAT_EQ(res.x, 3.0f);
  EXPECT_FLOAT_EQ(res.y, 4.0f);
  EXPECT_FLOAT_EQ(res.z, 5.0f);
}

TEST(TransformMatrixBuilderTest, RotationMatrixX) {
  auto m = TransformMatrixBuilder::CreateRotationMatrix(90.0, 0.0, 0.0);
  ThreeDPoint p(0.0f, 1.0f, 0.0f);
  ThreeDPoint res = m.TransformPoint(p);

  EXPECT_NEAR(res.x, 0.0f, 1e-5);
  EXPECT_NEAR(res.y, 0.0f, 1e-5);
  EXPECT_NEAR(res.z, 1.0f, 1e-5);
}

// -------------------------- Figure Tests ------------------------------

TEST(FigureTest, AddVertex) {
  Figure fig;
  auto v = std::make_shared<Vertex>(ThreeDPoint(1, 2, 3));
  fig.setVertices(v);

  EXPECT_EQ(fig.GetVertices().size(), 1);
  EXPECT_EQ(fig.GetVertices()[0]->GetPosition(), ThreeDPoint(1, 2, 3));
}

TEST(FigureTest, TransformationOrder) {
  Figure fig;
  fig.setScale(2.0f);
  fig.setMove(5.0f, 0.0f, 0.0f);
  fig.setRotate(0.0f, 90.0f, 0.0f);

  auto v = std::make_shared<Vertex>(ThreeDPoint(1, 0, 0));
  fig.setVertices(v);
  fig.setDataVertices(v->GetPosition());

  fig.Transform();

  ThreeDPoint res = fig.GetVertices()[0]->GetPosition();
  EXPECT_NEAR(res.x, 5.0f, 1e-5);
  EXPECT_NEAR(res.y, 0.0f, 1e-5);
  EXPECT_NEAR(res.z, -2.0f, 1e-5);
}

// ------------------------ FileReader Tests ----------------------------

TEST(FileReaderTest, VertexParsing) {
  std::string content = "v 1.0 2.0 3.0\nv 4.0 5.0 6.0";
  std::ofstream testFile("test.obj");
  testFile << content;
  testFile.close();

  NormalizationParameters params;
  Scene scene = FileReader().ReadScene("test.obj", params);

  auto fig = scene.GetFigures()[0];
  EXPECT_EQ(fig->GetVertices().size(), 2);

  float centerX = (1.0f + 4.0f) / 2;
  float centerY = (2.0f + 5.0f) / 2;
  float centerZ = (3.0f + 6.0f) / 2;
  ThreeDPoint expected(1.0f - centerX, 2.0f - centerY, 3.0f - centerZ);
  EXPECT_EQ(fig->GetVertices()[0]->GetPosition(), expected);
}

TEST(FileReaderTest, FaceParsing) {
  std::string content =
      "v 0 0 0\nv 1 0 0\nv 0 1 0\n"
      "f 1 2 3";
  std::ofstream testFile("test.obj");
  testFile << content;
  testFile.close();

  NormalizationParameters params;
  Scene scene = FileReader().ReadScene("test.obj", params);

  auto fig = scene.GetFigures()[0];
  EXPECT_EQ(fig->GetEdges().size(), 3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
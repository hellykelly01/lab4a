#include "BinaryTree.h"
#include "test_runner.h"

void TestConstruction(){
  BinaryTree<int, int> tree;
  tree.insertElement(7, 1);
  tree.insertElement(5, 1);
  tree.insertElement(6, 1);
  tree.insertElement(4, 1);
  tree.insertElement(1, 1);
  tree.insertElement(3, 1);
  tree.insertElement(9, 1);
  tree.insertElement(10, 1);
  tree.insertElement(11, 1);
  tree.insertElement(8, 1);
  tree.insertElement(2, 1);
  std::vector<int> expectedLNR = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  std::vector<int> expectedNLR = {7, 5, 4, 1, 3, 2, 6, 9, 8, 10, 11};
  ASSERT_EQUAL(tree.toVectorLNR(), expectedLNR);
  ASSERT_EQUAL(tree.toVectorNLR(), expectedNLR);
}

void TestCopy(){
  BinaryTree<int, int> tree;
  tree.insertElement(7, 1);
  tree.insertElement(5, 1);
  tree.insertElement(6, 1);
  tree.insertElement(4, 1);
  tree.insertElement(1, 1);
  tree.insertElement(3, 1);
  tree.insertElement(9, 1);
  tree.insertElement(10, 1);
  tree.insertElement(11, 1);
  tree.insertElement(8, 1);
  tree.insertElement(2, 1);
  BinaryTree<int, int> tree2 = tree;
  std::vector<int> expectedLNR = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  std::vector<int> expectedNLR = {7, 5, 4, 1, 3, 2, 6, 9, 8, 10, 11};
  ASSERT_EQUAL(tree.toVectorLNR(), expectedLNR);
  ASSERT_EQUAL(tree.toVectorNLR(), expectedNLR);
  ASSERT_EQUAL(tree2.toVectorLNR(), expectedLNR);
  ASSERT_EQUAL(tree2.toVectorNLR(), expectedNLR);
}

void TestMove(){
  BinaryTree<int, int> tree;
  tree.insertElement(7, 1);
  tree.insertElement(5, 1);
  tree.insertElement(6, 1);
  tree.insertElement(4, 1);
  tree.insertElement(1, 1);
  tree.insertElement(3, 1);
  tree.insertElement(9, 1);
  tree.insertElement(10, 1);
  tree.insertElement(11, 1);
  tree.insertElement(8, 1);
  tree.insertElement(2, 1);
  BinaryTree<int, int> tree2 = std::move(tree);
  std::vector<int> expectedLNR = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  std::vector<int> expectedNLR = {7, 5, 4, 1, 3, 2, 6, 9, 8, 10, 11};
  ASSERT_EQUAL(tree2.toVectorLNR(), expectedLNR);
  ASSERT_EQUAL(tree2.toVectorNLR(), expectedNLR);
  std::vector<int> empty;
  ASSERT(tree.toVectorNLR() == empty);
  ASSERT(tree.toVectorLNR() == empty);
}

void TestMultiKey(){
  BinaryTree<int, int> tree;
  tree.insertElement(4, 1);
  tree.insertElement(3, 1);
  tree.insertElement(6, 1);
  tree.insertElement(5, 1);
  tree.insertElement(1, 1);
  tree.insertElement(6, 2);
  tree.insertElement(6, 3);
  std::vector<int> expected = {1, 2, 3};
  ASSERT_EQUAL(tree.getAllElements(6).toVector(), expected);
}

void TestInsertElement(){
  BinaryTree<int, int> tree;
  std::vector<int> expectedLNR;
  ASSERT(tree.toVectorLNR() == expectedLNR);

  tree.insertElement(4, 1);
  expectedLNR = {4};
  ASSERT(tree.toVectorLNR() == expectedLNR);

  tree.insertElement(3, 1);
  expectedLNR = {3, 4};
  ASSERT(tree.toVectorLNR() == expectedLNR);

  tree.insertElement(6, 1);
  expectedLNR = {3, 4, 6};
  ASSERT(tree.toVectorLNR() == expectedLNR);

  tree.insertElement(5, 1);
  expectedLNR = {3, 4, 5, 6};
  ASSERT(tree.toVectorLNR() == expectedLNR);
  
  tree.insertElement(1, 1);
  expectedLNR = {1, 3, 4, 5, 6};
  ASSERT(tree.toVectorLNR() == expectedLNR);
  
  tree.insertElement(6, 1);
  expectedLNR = {1, 3, 4, 5, 6};
  ASSERT(tree.toVectorLNR() == expectedLNR);

  tree.insertElement(2, 1);
  expectedLNR = {1, 2, 3, 4, 5, 6};
  ASSERT(tree.toVectorLNR() == expectedLNR);
}

void TestRemoveElement(){
  BinaryTree<int, int> tree;
  tree.insertElement(7, 1);
  tree.insertElement(5, 1);
  tree.insertElement(6, 1);
  tree.insertElement(4, 1);
  tree.insertElement(1, 1);
  tree.insertElement(3, 1);
  tree.insertElement(9, 1);
  tree.insertElement(10, 1);
  tree.insertElement(11, 1);
  tree.insertElement(8, 1);
  tree.insertElement(2, 1);
  std::vector<int> expectedLNR = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  std::vector<int> expectedNLR = {7, 5, 4, 1, 3, 2, 6, 9, 8, 10, 11};
  ASSERT_EQUAL(tree.toVectorLNR(), expectedLNR);
  ASSERT_EQUAL(tree.toVectorNLR(), expectedNLR);

  tree.removeElement(6); // leaf removal
  expectedLNR = {1, 2, 3, 4, 5, 7, 8, 9, 10, 11};
  expectedNLR = {7, 5, 4, 1, 3, 2, 9, 8, 10, 11};
  ASSERT_EQUAL(tree.toVectorLNR(), expectedLNR);
  ASSERT_EQUAL(tree.toVectorNLR(), expectedNLR);

  tree.removeElement(5); // node removal (1 child)
  expectedLNR = {1, 2, 3, 4, 7, 8, 9, 10, 11};
  expectedNLR = {7, 4, 1, 3, 2, 9, 8, 10, 11};
  ASSERT_EQUAL(tree.toVectorLNR(), expectedLNR);
  ASSERT_EQUAL(tree.toVectorNLR(), expectedNLR);

  tree.removeElement(9); // node removal (2 children)
  expectedLNR = {1, 2, 3, 4, 7, 8, 10, 11};
  expectedNLR = {7, 4, 1, 3, 2, 10, 8, 11};
  ASSERT_EQUAL(tree.toVectorLNR(), expectedLNR);
  ASSERT_EQUAL(tree.toVectorNLR(), expectedNLR);

  tree.removeElement(7); // root removal
  expectedLNR = {1, 2, 3, 4, 8, 10, 11};
  expectedNLR = {8, 4, 1, 3, 2, 10, 11};
  ASSERT_EQUAL(tree.toVectorLNR(), expectedLNR);
  ASSERT_EQUAL(tree.toVectorNLR(), expectedNLR);

}

void TestGetElement(){
  BinaryTree<int, int> tree;
  tree.insertElement(7, 1);
  tree.insertElement(5, 1);
  tree.insertElement(6, 1);
  tree.insertElement(4, 1);
  tree.insertElement(1, 1);
  tree.insertElement(3, 1);
  tree.insertElement(9, 1);
  tree.insertElement(10, 1);
  tree.insertElement(11, 1);
  tree.insertElement(8, 1);
  tree.insertElement(2, 1);
  ASSERT(tree.getElement(4) == 1);
  tree.insertElement(4, 2);
  ASSERT(tree.getElement(4) == 2);
  tree.insertElement(4, 3);
  ASSERT(tree.getElement(4) == 3);
  tree.removeElement(4);
  ASSERT(tree.getElement(4) == 3);
  tree.removeElement(4);
  ASSERT(tree.getElement(4) == 3);
}

void TestFindFirstGreater(){
  BinaryTree<int, int> tree;
  tree.insertElement(7, 1);
  tree.insertElement(5, 1);
  tree.insertElement(6, 1);
  tree.insertElement(4, 1);
  tree.insertElement(1, 1);
  tree.insertElement(3, 1);
  tree.insertElement(9, 1);
  tree.insertElement(10, 1);
  tree.insertElement(11, 1);
  tree.insertElement(8, 1);
  tree.insertElement(2, 1);
  ASSERT(tree.findFirstGreater(0) == 1);
  ASSERT(tree.findFirstGreater(1) == 2);
  ASSERT(tree.findFirstGreater(2) == 3);
  ASSERT(tree.findFirstGreater(3) == 4);
  ASSERT(tree.findFirstGreater(4) == 5);
  ASSERT(tree.findFirstGreater(5) == 6);
  ASSERT(tree.findFirstGreater(6) == 7);
  ASSERT(tree.findFirstGreater(7) == 8);
  ASSERT(tree.findFirstGreater(8) == 9);
  ASSERT(tree.findFirstGreater(9) == 10);
  ASSERT(tree.findFirstGreater(10) == 11);
}

int main(){
  TestRunner tr;
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestCopy);
  RUN_TEST(tr, TestMove);
  RUN_TEST(tr, TestMultiKey);
  RUN_TEST(tr, TestInsertElement);
  RUN_TEST(tr, TestRemoveElement);
  RUN_TEST(tr, TestGetElement);
  RUN_TEST(tr, TestFindFirstGreater);
  
  return 0;
}
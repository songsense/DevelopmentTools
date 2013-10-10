//
//  Test.h
//  CrackingCodingInterview
//
//  Created by 宋思明 on 6/29/13.
//  Copyright (c) 2013 宋思明. All rights reserved.
//

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <sys/time.h>
#include "Tools.h"

using namespace std;

class TestBase  {
protected:
  inline void PrintTitle(ofstream &fout, const string &info) {
    fout<<"<!DOCTYPE html><head>";
    fout<<"<style>";
    fout<<"#tables";
    fout<<"{";
    fout<<"font-family:\"Trebuchet MS\", Arial, Helvetica, sans-serif;";
    fout<<"width:100%;";
    fout<<"border-collapse:collapse;";
    fout<<"text-align:center;";
    fout<<"vertical-align:middle;";
    fout<<"}";
    fout<<"#tables td, #tables th";
    fout<<"{";
    fout<<"font-size:0.8em;";
    fout<<"border:1px solid #98bf21;";
    fout<<"padding:3px 7px 2px 7px;";
    fout<<"}";
    fout<<"#tables th";
    fout<<"{";
    fout<<"font-size:1em;";
    fout<<"padding-top:5px;";
    fout<<"padding-bottom:4px;";
    fout<<"background-color:#A7C942;";
    fout<<"color:#fff;";
    fout<<"}";
    fout<<"#tables tr td ";
    fout<<"{";
    fout<<"color:green";
    fout<<"}";
    fout<<"#tables tr.fail td ";
    fout<<"{";
    fout<<"background-color:#EAF2D3;";
    fout<<"color:red;";
    fout<<"}";
    fout<<"</style>";
    fout<<"</head><html><body>";
    fout<<"<h2>"<<info<<"</h2>";
    cout<<info<<'\n';
  }
  inline void CreateTable(ofstream &fout) {
    fout<<"<table id=\"tables\" >";
    fout<<"<tr><th>note</th><th>output</th><th>expected</th><th>result</th></tr>";
    cout<<"note\toutput\texpected\tresult\n";
  }
  inline void EndTable(ofstream &fout) {
    fout<<"</table>";
  }
  inline void CreateRow(ofstream &fout, const string &input,const string &output,
                        const string &expected, const bool &result) {
    if (result) {
      fout<<"<tr><td>"<<input<<"</td>"<<"<td>"<<output<<"</td><td>"<<expected<<"</td>"<<"<td>pass!</td></tr>";
      passCount++;
    }
    else
      fout<<"<tr class=\"fail\"><td>"<<input<<"</td>"<<"<td>"<<output<<"</td><td>"<<expected<<"</td>"<<"<td>fail!</td></tr>";
    testCount++;
  }
  void OpenLogFile(ofstream &fout, const string &filename, const string &info) {
    string filePlace("./TestResults/");
    filePlace += filename;
    remove(filePlace.c_str());
    fout.open(filePlace,std::ofstream::out | std::ofstream::app);
    PrintTitle(fout,info);
    CreateTable(fout);
    testUnitCount++;
    testCount = 0;
    passCount = 0;
    gettimeofday(&testUnitStartTime, NULL);
  }
  void CloseLogFile(ofstream &fout) {
    gettimeofday(&testUnitStopTime, NULL);
    double elapsedTime((testUnitStopTime.tv_sec - testUnitStartTime.tv_sec) * 1000.0);
    elapsedTime += (testUnitStopTime.tv_usec - testUnitStartTime.tv_usec) / 1000.0;
    cout<<passCount<<'/'<<testCount<<" test cases are passed!.\nThe tests took "<<elapsedTime<<"ms. The average running time is "<<elapsedTime/testCount<<"ms.\n";
    EndTable(fout);
    fout<<"<p>"<<passCount<<" out of "<<testCount<<" test cases are passed!"<<"</p>";
    fout<<"<p>"<<"The tests run "<<elapsedTime<<"ms. The average running time is "<<elapsedTime/testCount<<"ms. </p>"<<"</body></html>";
    cout.flush();
    fout.flush();
    fout.close();
  }
  Tools tools;
  // The count of unit tst made
  unsigned long testUnitCount;
  // The count of each test made
  unsigned long testCount;
  unsigned long passCount;
  timeval testUnitStartTime;
  timeval testUnitStopTime;
  timeval testStartTime;
  timeval testStopTime;
public:
  TestBase() : testUnitCount(0) {}
  template<typename T>
  int TestLTnEq(ofstream &fout, const string &input, const T &output, const T &expected) {
    cout<<output<<'\t'<<expected<<'\t';
    stringstream ss_output, ss_expected;
    string s_output, s_expected;
    ss_output<<output; ss_output>>s_output;
    ss_expected<<expected; ss_expected>>s_expected;
    cout<<input<<'\t'<<s_output<<'\t'<<s_expected<<'\t';
    if (output <= expected) {
      cout<<"pass\n";
      CreateRow(fout, input, s_output, s_expected, true);
      return 1;
    }
    else {
      cout<<"fail\n";
      CreateRow(fout, input, s_output, s_expected, false);
      return 0;
    }
  }
  template<typename T>
  int TestGTnEq(ofstream &fout, const string &input, const T &output, const T &expected) {
    cout<<output<<'\t'<<expected<<'\t';
    stringstream ss_output, ss_expected;
    string s_output, s_expected;
    ss_output<<output; ss_output>>s_output;
    ss_expected<<expected; ss_expected>>s_expected;
    cout<<input<<'\t'<<s_output<<'\t'<<s_expected<<'\t';
    if (output >= expected) {
      cout<<"pass\n";
      CreateRow(fout, input, s_output, s_expected, true);
      return 1;
    }
    else {
      cout<<"fail\n";
      CreateRow(fout, input, s_output, s_expected, false);
      return 0;
    }
  }
  template<typename T>
  int TestLT(ofstream &fout, const string &input, const T &output, const T &expected) {
    cout<<output<<'\t'<<expected<<'\t';
    stringstream ss_output, ss_expected;
    string s_output, s_expected;
    ss_output<<output; ss_output>>s_output;
    ss_expected<<expected; ss_expected>>s_expected;
    cout<<input<<'\t'<<s_output<<'\t'<<s_expected<<'\t';
    if (output < expected) {
      cout<<"pass\n";
      CreateRow(fout, input, s_output, s_expected, true);
      return 1;
    }
    else {
      cout<<"fail\n";
      CreateRow(fout, input, s_output, s_expected, false);
      return 0;
    }
  }
  template<typename T>
  int TestGT(ofstream &fout, const string &input, const T &output, const T &expected) {
    cout<<output<<'\t'<<expected<<'\t';
    stringstream ss_output, ss_expected;
    string s_output, s_expected;
    ss_output<<output; ss_output>>s_output;
    ss_expected<<expected; ss_expected>>s_expected;
    cout<<input<<'\t'<<s_output<<'\t'<<s_expected<<'\t';
    if (output > expected) {
      cout<<"pass\n";
      CreateRow(fout, input, s_output, s_expected, true);
      return 1;
    }
    else {
      cout<<"fail\n";
      CreateRow(fout, input, s_output, s_expected, false);
      return 0;
    }
  }
  int TestDouble(ofstream &fout, const string &input, const double &output, const double &expected, const double& precision = 1e-7) {
    cout<<output<<'\t'<<expected<<'\t';
    stringstream ss_output, ss_expected;
    string s_output, s_expected;
    ss_output<<output; ss_output>>s_output;
    ss_expected<<expected; ss_expected>>s_expected;
    cout<<input<<'\t'<<s_output<<'\t'<<s_expected<<'\t';
    if (abs(expected - output) <= precision) {
      cout<<"pass\n";
      CreateRow(fout, input, s_output, s_expected, true);
      return 1;
    }
    else {
      cout<<"fail\n";
      CreateRow(fout, input, s_output, s_expected, false);
      return 0;
    }
  }
  template<typename T>
  int TestBasic(ofstream &fout, const string &input, const T &output, const T &expected) {
    cout<<output<<'\t'<<expected<<'\t';
    stringstream ss_output, ss_expected;
    string s_output, s_expected;
    ss_output<<output; s_output = ss_output.str();
    ss_expected<<expected; s_expected = ss_expected.str();
    cout<<input<<'\t'<<s_output<<'\t'<<s_expected<<'\t';
    if (expected == output) {
      cout<<"pass\n";
      CreateRow(fout, input, s_output, s_expected, true);
      return 1;
    }
    else {
      cout<<"fail\n";
      CreateRow(fout, input, s_output, s_expected, false);
      return 0;
    }
  }
  template<typename T>
  int TestMatrix(ofstream &fout, const string &input,
                 const vector<vector<T> > &output, const vector<vector<T> > &expected) {
    stringstream ss_output, ss_expected;
    tools.PrintMatrix(output);
    tools.PrintMatrix2File(output, ss_output);
    tools.PrintMatrix(expected);
    tools.PrintMatrix2File(expected, ss_expected);
    if (output.empty()&& expected.empty()) {
      cout<<"pass\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), true);
      return 1;
    }
    if ((output.empty() && !expected.empty()) ||
        (!output.empty() && expected.empty())) {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
    unsigned long rowOutput(output.size()), rowExpected(expected.size());
    if (rowOutput != rowExpected) {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
    for (size_t i = 0; i < rowOutput; i++) {
      unsigned long colOutput(output[i].size()), colExpected(expected[i].size());
      if (colOutput != colExpected) {
        cout<<"fail\n";
        CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
        return 0;
      }
      for (size_t j = 0; j < colOutput; j++) {
        if (output[i][j] != expected[i][j]) {
          cout<<"fail\n";
          CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
          return 0;
        }
      }
    }
    cout<<"pass\n";
    CreateRow(fout, input, ss_output.str(), ss_expected.str(), true);
    return 1;
  }
  template<typename T>
  int TestDynamicArrayInOrder(ofstream &fout, const string &input, const vector<T> &output, const vector<T> &expected) {
    ostringstream ss_output, ss_expected;
    tools.PrintVector(output);
    tools.PrintVector2File(output, ss_output);
    tools.PrintVector(expected);
    tools.PrintVector2File(expected, ss_expected);
    if (output.empty()&& expected.empty()) {
      cout<<"pass\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), true);
      return 1;
    }
    if ((output.empty() && !expected.empty()) ||
        (!output.empty() && expected.empty())) {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
    size_t lenOutput(output.size()), lenExpected(expected.size());
    if (lenOutput != lenExpected) {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
    for (size_t i = 0; i < lenOutput; i++) {
      if (output[i] != expected[i]) {
        cout<<"fail\n";
        CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
        return 0;
      }
    }
    cout<<"pass\n";
    CreateRow(fout, input, ss_output.str(), ss_expected.str(), true);
    return 1;
  }
  template<typename T>
  int TestDynamicArray(ofstream &fout, const string &input, const vector<T> &output, const vector<T> &expected) {
    ostringstream ss_output, ss_expected;
    tools.PrintVector(output);
    tools.PrintVector2File(output, ss_output);
    tools.PrintVector(expected);
    tools.PrintVector2File(expected, ss_expected);
    if (output.empty()&& expected.empty()) {
      cout<<"pass\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), true);
      return 1;
    }
    if ((output.empty() && !expected.empty()) ||
        (!output.empty() && expected.empty())) {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
    size_t lenOutput(output.size()), lenExpected(expected.size());
    if (lenOutput != lenExpected) {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
    bool pass(true);
    vector<char> isUsed(lenExpected,0);
    size_t matchedNum(0);
    for (size_t i = 0; i < lenOutput; i++) {
      bool isExisted(false);
      for (size_t j = 0; j < lenOutput; j++) {
        if (isUsed[j] == 1)
          continue;
        if (output[i] == expected[j]) {
          isUsed[j] = 1;
          isExisted = true;
          matchedNum++;
          break;
        }
      }
      if (!isExisted) {
        pass = false;
        break;
      }
    }
    if (pass && matchedNum == lenOutput) {
      cout<<"pass\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), true);
      return 1;
    }
    else {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
  }
  template<typename T>
  int TestStaticArray(ofstream &fout, const string &input, const T *output, const T *expected,
                      const unsigned long &lenOutput, const unsigned long &lenExpected) {
    stringstream ss_output, ss_expected;
    cout<<input<<'\t';
    for (size_t i = 0; i < lenOutput; i++) {
      cout<<output[i];
      ss_output<<output[i];
    }
    cout<<'\t';
    for (size_t i = 0; i < lenExpected; i++) {
      cout<<expected[i];
      ss_expected<<expected[i];
    }
    cout<<'\t';
    if (lenOutput != lenExpected) {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
    for (size_t i = 0; i < lenOutput; i++) {
      if (output[i] != expected[i]) {
        cout<<"fail\n";
        CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
        return 0;
      }
    }
    cout<<"pass\n";
    CreateRow(fout, input, ss_output.str(), ss_expected.str(), true);
    return 1;
  }
  int TestLinkedList(ofstream &fout, const string &input, ListNode *output, ListNode * expected) {
    stringstream ss_output, ss_expected;
    output->PrintListNode(output, ss_output);
    expected->PrintListNode(expected, ss_expected);
    cout<<input<<'\t'<<ss_output.str()<<'\t'<<ss_expected.str()<<'\t';

    while (output != nullptr && expected != nullptr) {
      if (output->val != expected->val) {
        cout<<"fail\n";
        CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
        return 0;
      }
      output = output->next, expected = expected->next;
    }
    if ((output != nullptr && expected == nullptr) ||
        (output == nullptr && expected != nullptr)) {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
    cout<<"pass\n";
    CreateRow(fout, input, ss_output.str(), ss_expected.str(), true);
    return 1;
  }
  int TestTree(ofstream &fout, const string &input, Tree *output, Tree *expected) {
    ostringstream ss_coutput, ss_cout_expected, ss_output, ss_expected;
    Tree::PrintTree(output, ss_coutput);
    Tree::PrintTree(expected, ss_cout_expected);
    Tree::PrintTree2File(output, ss_output);
    Tree::PrintTree2File(expected, ss_expected);
    cout<<ss_coutput.str()<<'\t'<<ss_cout_expected.str()<<'\t';

    if (ss_output.str() == ss_expected.str()) {
      cout<<"pass\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), true);
      return 1;
    }
    else {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
  }
  template<typename T, typename U>
  int TestGraph(ofstream &fout, const string &input, Graph<T,U> &output, Graph<T,U> &expected) {
    ostringstream ss_coutput, ss_cout_expected, ss_output, ss_expected;
    output.PrintGraph(ss_coutput);
    expected.PrintGraph(ss_cout_expected);
    output.PrintGraph2File(ss_output);
    expected.PrintGraph2File(ss_expected);
    cout<<ss_coutput.str()<<'\t'<<ss_cout_expected.str()<<'\t';

    if (ss_output.str() == ss_expected.str()) {
      cout<<"pass\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), true);
      return 1;
    }
    else {
      cout<<"fail\n";
      CreateRow(fout, input, ss_output.str(), ss_expected.str(), false);
      return 0;
    }
  }
  // Global count
  //void setTestUnitCount(unsigned long c) { testUnitCount = c;}
  unsigned long getGlobalCount(unsigned long c) { return testUnitCount;}
  //void resetGlobalCount(void) { testUnitCount = 0;}
  //void setTestCount(unsigned long c) { testCount = c;}
  unsigned long getTestCount(unsigned long c) { return testCount;}
  //void resetTestCount(void) { testCount = 0;}
};

class Test: public TestBase {
public:
  /////// Test
};

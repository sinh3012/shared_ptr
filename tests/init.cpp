#include "shared_ptr.hpp"
#include <iostream>
#include <catch.hpp>

SCENARIO("Init", "[Init]"){
  shared_ptr<int> ptr;
  REQUIRE(ptr.get() == nullptr);
  REQUIRE(ptr.use_count() == 0);
  REQUIRE(ptr.unique() == false);
  REQUIRE(bool(ptr) == false);
}

SCENARIO("Init with ptr", "[Init ptr]"){
  shared_ptr<int> ptr(new int(404));
  REQUIRE(*ptr == 404);
  REQUIRE(ptr.use_count() == 1);
  REQUIRE(ptr.unique() == true);
  REQUIRE(bool(ptr) == true);
}

SCENARIO("Copy init", "[Copy init]"){
  shared_ptr<int> ptr(new int(404));
  shared_ptr<int> ptr1(ptr);
  REQUIRE(*ptr1 == 404);
  REQUIRE(ptr1.use_count() == 2);
  REQUIRE(ptr1.unique() == false);
}

SCENARIO("Copy operator", "[Copy operator]"){
  shared_ptr<int> ptr(new int(404));
  shared_ptr<int> ptr1;
  ptr1 = ptr;
  REQUIRE(*ptr1 == 404);
  REQUIRE(ptr1.use_count() == 2);
  REQUIRE(ptr1.unique() == false);
}

SCENARIO("Move init", "[Move init]"){
  shared_ptr<int> ptr(new int(404));
  shared_ptr<int> ptr1(std::move(ptr));
  REQUIRE(*ptr1 == 404);
  REQUIRE(ptr.get() == nullptr);
  REQUIRE(ptr1.use_count() == 1);
  REQUIRE(ptr.use_count() == 0);
  REQUIRE(ptr1.unique() == true);
}

SCENARIO("Move operator", "[Move operator]"){
  shared_ptr<int> ptr(new int(404));
  shared_ptr<int> ptr1;
  ptr1 = std::move(ptr);
  REQUIRE(*ptr1 == 404);
  REQUIRE(ptr.get() == nullptr);
  REQUIRE(ptr1.use_count() == 1);
  REQUIRE(ptr.use_count() == 0);
  REQUIRE(ptr1.unique() == true);
}

SCENARIO("Reset", "[Reset]"){
  shared_ptr<int> ptr(new int(404));
  shared_ptr<int> ptr1(ptr);
  ptr.reset();
  REQUIRE(ptr1.use_count() == 1);
  REQUIRE(ptr1.unique() == true);
}

SCENARIO("Swap", "[Swap]"){
  shared_ptr<int> ptr(new int(404));
  shared_ptr<int> ptr1(new int(24));
  ptr.swap(ptr1);
  REQUIRE(*ptr == 24);
  REQUIRE(*ptr1 == 404);
}

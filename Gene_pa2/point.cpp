/*
Copyright 2008 Intel Corporation

Use, modification and distribution are subject to the Boost Software License,
Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt).
*/
#include <boost/polygon/polygon.hpp>
#include <cassert>
namespace gtl = boost::polygon;
using namespace boost::polygon::operators;

int main() {
  //constructing a gtl point
  typedef gtl::point_data<int> Point;
  int x = 10;
  int y = 20;
  Point pt(x, y);
  assert(gtl::x(pt) == 10);
  assert(gtl::y(pt) == 20);
  
  //a quick primer in isotropic point access
  typedef gtl::orientation_2d O;
  using gtl::HORIZONTAL;
  using gtl::VERTICAL;
  O o = HORIZONTAL;
  assert(gtl::x(pt) == gtl::get(pt, o));
  
  o = o.get_perpendicular();
  assert(o == VERTICAL);
  assert(gtl::y(pt) == gtl::get(pt, o));

  gtl::set(pt, o, 30);
  assert(gtl::y(pt) == 30);

  //using some of the library functions
  Point pt2(10, 30);
  assert(gtl::equivalence(pt, pt2));

  gtl::transformation<int> tr(gtl::axis_transformation::SWAP_XY);
  gtl::transform(pt, tr);
  assert(gtl::equivalence(pt, Point(30, 10)));

  gtl::transformation<int> tr2 = tr.inverse();
  assert(tr == tr2); //SWAP_XY is its own inverse transform

  gtl::transform(pt, tr2);
  assert(gtl::equivalence(pt, pt2)); //the two points are equal again

  gtl::move(pt, o, 10); //move pt 10 units in y
  assert(gtl::euclidean_distance(pt, pt2) == 10.0f);

  gtl::move(pt, o.get_perpendicular(), 10); //move pt 10 units in x
  assert(gtl::manhattan_distance(pt, pt2) == 20);

  return 0;
}
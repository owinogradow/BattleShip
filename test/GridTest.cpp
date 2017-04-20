#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>
#include <utility>

#include "Grid.h"

using namespace std;

BOOST_AUTO_TEST_CASE(GridConstructorTest)
{
	Grid grid;
	BOOST_CHECK_EQUAL(grid.valueAt(5, 5), 0);
}

BOOST_AUTO_TEST_CASE(MarkShipTest)
{
	Grid grid;
	grid.markShip(make_pair(5, 5));
	BOOST_CHECK_EQUAL(grid.valueAt(5, 5), 2);
}

BOOST_AUTO_TEST_CASE(valueAtTest)
{
	Grid grid;
	BOOST_CHECK_EQUAL(grid.valueAt(5, 5), 0);
}

BOOST_AUTO_TEST_CASE(wasAHitTest)
{
	Grid grid;
	grid.markShip(make_pair(5, 5));
	BOOST_CHECK_EQUAL(grid.wasAHit(make_pair(5, 5)), true);
}

BOOST_AUTO_TEST_CASE(wasAMissTest)
{
	Grid grid;
	BOOST_CHECK_EQUAL(grid.wasAMiss(make_pair(5, 5)), true);
}

BOOST_AUTO_TEST_CASE(wasAlreadyATargetTest)
{
	Grid grid;
	grid.markTarget(make_pair(5, 5));
	BOOST_CHECK_THROW(grid.wasAlreadyATarget(make_pair(5, 5)), invalid_argument);
}

BOOST_AUTO_TEST_CASE(markTargetTest)
{
	Grid grid;
	grid.markShip(make_pair(5, 5));
	grid.markTarget(make_pair(5, 5));
	BOOST_CHECK_EQUAL(grid.valueAt(5, 5), 1);
}


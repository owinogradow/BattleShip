#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>
#include <utility>

#include "Ship.h"
#include "SingleFunnel.h"
#include "MultipleFunnel.h"

using namespace std;

BOOST_AUTO_TEST_CASE(SingleFunnelConstructorTest)
{
	Grid* secondaryGrid = new Grid;

	vector < pair <int, int>> coordinates{ {4,4} };
	SingleFunnel ship(coordinates, true, secondaryGrid);
	BOOST_CHECK_EQUAL(ship.belongsToHuman(), true);
	BOOST_CHECK_EQUAL(ship.getSize(), 1);
	BOOST_CHECK_EQUAL(ship.getRange(), 2);

	coordinates.push_back(make_pair(4, 5));
	MultipleFunnel multipleship(coordinates, true, secondaryGrid);
	BOOST_CHECK_EQUAL(multipleship.getSize(), 2);
	BOOST_CHECK_EQUAL(multipleship.getRange(), 3);

	delete secondaryGrid;
}

BOOST_AUTO_TEST_CASE(isInRangeTest)
{
	Grid* secondaryGrid = new Grid;
	vector < pair <int, int>> coordinates{ {4,4} };
	SingleFunnel ship(coordinates,true,secondaryGrid);
	BOOST_CHECK_THROW(ship.isInRange(make_pair(7,7)), invalid_argument);

	//multiple funnel test section

	coordinates.push_back(make_pair(4, 5));
	MultipleFunnel multiship(coordinates);
	BOOST_CHECK_EQUAL(multiship.isInRange(make_pair(6, 6)), true);

	delete secondaryGrid; 
}

BOOST_AUTO_TEST_CASE(isSunkTest)
{
	vector < pair <int, int>> coordinates{ {4,4} };
	SingleFunnel ship(coordinates);
	BOOST_CHECK_EQUAL(ship.isSunk(), false);
}
BOOST_AUTO_TEST_CASE(getRangeTest)
{
	vector < pair <int, int>> coordinates{ {4,4} };
	SingleFunnel ship(coordinates);
	BOOST_CHECK_EQUAL(ship.getRange(), 2);

	//multiple funnel test section

	coordinates.push_back(make_pair(4, 5));
	MultipleFunnel multiship(coordinates);
	BOOST_CHECK_EQUAL(multiship.getRange(), 3);
}

                            
BOOST_AUTO_TEST_CASE(PossibleTargetTest)
{
	// single ship test section
	Grid* grid = new Grid;
	vector < pair <int, int>> coordinates{ {4,4} };
	SingleFunnel ship(coordinates,1, grid);
	BOOST_CHECK_EQUAL(ship.possibleTargets().size(),25);
	vector < pair <int, int>> coordinates2{ {0,0} };
	SingleFunnel ship2(coordinates2,1,grid);
	BOOST_CHECK_EQUAL(ship2.possibleTargets().size(),9);

	// multiple ship test section
	
	vector < pair<int, int> > coordinates3{ {5,5},{5,6} };
	MultipleFunnel multiship(coordinates3, 1, grid);
	BOOST_CHECK_EQUAL(multiship.possibleTargets().size(),56);
	vector < pair<int, int> > coordinates4{ {0,0},{0,1} };
	MultipleFunnel multifunnel(coordinates4,1,grid);
	BOOST_CHECK_EQUAL(multifunnel.possibleTargets().size(),20);
	
	delete grid;
}

BOOST_AUTO_TEST_CASE(isReloadedTest)
{
	vector < pair <int, int>> coordinates{ {4,4} };
	SingleFunnel ship(coordinates);
	BOOST_CHECK_EQUAL(ship.isReloaded(), false);

	//multiple funnel test section

	coordinates.push_back(make_pair(4, 5));
	MultipleFunnel multiship(coordinates);
	multiship.fire();
	multiship.fire();
	BOOST_CHECK_EQUAL(multiship.isReloaded(), true);
}

BOOST_AUTO_TEST_CASE(intactSegmentTest)
{
	vector < pair <int, int>> coordinates{ {4,4} };
	SingleFunnel ship(coordinates);
	BOOST_CHECK_EQUAL(ship.intactSegments(), 1);

	//multiple funnel test section

	coordinates.push_back(make_pair(4, 5));
	MultipleFunnel multiship(coordinates);
	BOOST_CHECK_EQUAL(multiship.intactSegments(), 2);
}

BOOST_AUTO_TEST_CASE(belongToHumanTest)
{
	vector < pair <int, int>> coordinates{ {4,4} };
	SingleFunnel ship(coordinates);
	BOOST_CHECK_EQUAL(ship.belongsToHuman(), true);
}

BOOST_AUTO_TEST_CASE(canTakeShotTest)
{
	Grid* grid = new Grid;
	vector < pair <int, int>> coordinates{ {4,4} };
	SingleFunnel ship(coordinates, 1, grid);
	BOOST_CHECK_EQUAL(ship.canTakeShot(), true);

	//multiple funnel test section
	coordinates.push_back(make_pair(4, 5));
	MultipleFunnel multiship(coordinates, 1, grid);
	BOOST_CHECK_EQUAL(multiship.canTakeShot(), true);

	delete grid;
}

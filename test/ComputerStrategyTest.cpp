#include <boost/test/unit_test.hpp>
#include <iostream>
#include <vector>

#include "ComputerPlayer.h"
#include "Greedy.h"
#include "Random.h"

using namespace std;

BOOST_AUTO_TEST_CASE(GreedyTest)
{
	ComputerPlayer player("greedy");
	player.createShips(1);
	player.createShips(2);
	player.createShips(3);
	Ship* tested = &(player.getShip(1));
	int nr_funnels = tested->getSize();
	BOOST_CHECK_EQUAL(nr_funnels, 2);
	player.setShipToFire();
	BOOST_CHECK_EQUAL(player.getSelected().getSize(), 3);
}

BOOST_AUTO_TEST_CASE(RandomTest)
{
	ComputerPlayer player("random");
	player.createShips(1);
	player.createShips(2);
	player.createShips(3);
	Ship* tested = &(player.getShip(1));
	int nr_funnels = tested->getSize();
	BOOST_CHECK_EQUAL(nr_funnels, 2);
	player.setShipToFire();
	BOOST_CHECK(player.getSelected().getSize() <= 3);
	BOOST_CHECK(player.getSelected().getSize() >= 0 );
}
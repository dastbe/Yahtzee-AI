# Builds all possible combinations of keep sets
# Used by Game AI for constructing choices during the game
#
# Created by: David Bell
# March 24th, 2012

import itertools

# outputs all possible keep-set masks
for keep_set in [p for p in itertools.product([0,1],repeat=5)]:
	print keep_set[0], keep_set[1], keep_set[2], keep_set[3], keep_set[4]
# Launches the RSD unit test
# The results obtained should be 0 4/7 and 1
# Might need to zoom out of the python plot to see the results more clearly

../../src/fsaplf $(cat argfsaplf)
python ../../python/plotSuspended.py out/out_suspended

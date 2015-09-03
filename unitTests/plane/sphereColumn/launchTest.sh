rm out/*
fsaplf $(cat argfsaplf)
python ../../../python/plotPorosity.py out/out_plane_1000
echo "Test is over, pressing enter will clean directory"
read input
rm out/*

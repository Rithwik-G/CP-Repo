
mkdir $1
cp template.cpp $1
cd $1	
mv template.cpp $1.cpp
subl $1.cpp

git add .
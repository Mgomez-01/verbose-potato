echo "Setting up folder for project $1"
mkdir $1 
cd $1 
echo "Creating a set of starting files for the project."
touch "$1_first.txt"
touch "README.md"

echo "# This is an example of a markdown setup for this project. 

## All information for this will be contained here and updated if need be." >> README.md



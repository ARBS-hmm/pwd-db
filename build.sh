#!/run/current-system/sw/bin/zsh

# Set paths for directories
ROOT_DIR=$(pwd)  # Current directory (root of the project)
MODULES_DIR="${ROOT_DIR}/modules-ig"
INCLUDE_DIR="${ROOT_DIR}/include"
LIB_DIR="${ROOT_DIR}/lib"

# Create lib directory if it doesn't exist
mkdir -p "$LIB_DIR"

cp $ROOT_DIR/lib/io.so $ROOT_DIR/modules-ig/fileHandlers/
cp $ROOT_DIR/lib/user.so $ROOT_DIR/modules-ig/fileHandlers/
echo "Copied the dumb so files"

# Compile all .c files in the modules-ig directory into .so files in the lib directory
echo "Compiling .c files in ${MODULES_DIR} into .so files..."
for file in ${MODULES_DIR}/*/*.c; do
  # Extract filename without extension
  filename=$(basename "$file" .c)
  
  # Compile each .c file into a shared object (.so) file and place it in lib/
  gcc -shared -fPIC -I "$INCLUDE_DIR" "$file" -o "$LIB_DIR/lib${filename}.so"
done

# Check if any shared libraries exist in the lib directory
LIBRARY_FILES=$(ls "$LIB_DIR"/lib*.so)
if [ -z "$LIBRARY_FILES" ]; then
  echo "No shared libraries found in $LIB_DIR. Exiting."
  exit 1
fi

# Explicitly list the libraries to link (example: -l module1 -l module2)
# Modify this list based on the actual libraries you have compiled
echo "Compiling main.c into a single a.out..."
gcc -I "$INCLUDE_DIR" -L "$LIB_DIR" -o "$ROOT_DIR/a.out" "$ROOT_DIR/main.c" -l fileHandlers -l loggers -l user

# Output result
echo "Build complete. Executable is located in ${ROOT_DIR}/a.out"

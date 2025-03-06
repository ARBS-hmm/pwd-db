#!/run/current-system/sw/bin/zsh

# Define the source directories
MODULES_IG_DIR="modules-ig"
LIB_DIR="lib"

# Create the lib directory if it doesn't exist
mkdir -p $LIB_DIR

# Iterate through each module in modules-ig directory
for module_dir in $MODULES_IG_DIR/*/; do
    module_name=$(basename $module_dir)
    echo "Compiling module: $module_name into shared object (.so) files..."

    # Compile all .c files in the module directory into object files (.o)
    for c_file in $module_dir*.c; do
        if [[ $c_file == *.c ]]; then
            # Compile each .c file into an object file (.o)
            gcc -fPIC -c $c_file -o $LIB_DIR/$(basename $c_file .c).o
        fi
    done

    # Link all object files into a shared library (.so)
    gcc -shared -o $LIB_DIR/lib$module_name.so $LIB_DIR/*.o

    # Clean up object files after creating the .so file
    rm $LIB_DIR/*.o

    echo "$module_name shared object compiled as $LIB_DIR/lib$module_name.so"
done

echo "All modules compiled into shared objects."

import os
import sys
import shutil

def generate_project(day, part):
    base_dir = os.getcwd()  # Get the current working directory
    day_folder = f"Day{day}"
    part_folder = f"part{part}"
    project_name = f"AOC2024_d{day}p{part}"
    cmake_content = f"""cmake_minimum_required(VERSION 3.10)

project({project_name})

set(CMAKE_CXX_STANDARD 26)

include_directories(${{CMAKE_SOURCE_DIR}}/include)

add_compile_options(-ggdb3)

add_executable({project_name} main.cpp)
target_link_libraries({project_name} PRIVATE stdc++exp)
"""

    # Full path to the part folder
    target_dir = os.path.join(base_dir, day_folder, part_folder)
    include_src = os.path.join(base_dir, "include")
    include_dest = os.path.join(target_dir, "include")

    try:
        # Check and create directories
        if os.path.exists(target_dir):
            print(f"Error: The folder {target_dir} already exists.")
            return
        os.makedirs(target_dir)
        
        # Copy the include folder
        if not os.path.exists(include_src):
            print(f"Error: The source 'include' folder does not exist in {base_dir}.")
            return
        shutil.copytree(include_src, include_dest)
        
        # Create the CMakeLists.txt file
        cmake_path = os.path.join(target_dir, "CMakeLists.txt")
        with open(cmake_path, "w") as cmake_file:
            cmake_file.write(cmake_content)
        
        print(f"Project created successfully in {target_dir}.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python script.py <day> <part>")
        sys.exit(1)
    
    day = sys.argv[1]
    part = sys.argv[2]
    
    if not day.isdigit() or not part.isdigit():
        print("Error: Both day and part must be numeric.")
        sys.exit(1)
    
    generate_project(int(day), int(part))

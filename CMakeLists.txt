
cmake_minimum_required(VERSION 4.0)
project(slk_defs1 VERSION 1.0.0)

# 1. Definicja Targetu Biblioteki Nagłówkowej
# Target INTERFACE oznacza, że nie ma plików .cpp do kompilacji.
add_library(slk_defs1 INTERFACE)

# 2. Ustawienie Ścieżek Nagłówkowych
# Używamy PUBLIC/INTERFACE, aby poinformować inne projekty,
# gdzie szukać nagłówków.

# Ta linia dodaje katalog "include" do ścieżek nagłówkowych.
# Inne projekty będą mogły używać #include <mojabiblioteka/defs1.hpp>
target_include_directories(slk_defs1 INTERFACE
# Ścieżka względem tego CMakeLists.txt
${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 3. Instalacja (Opcjonalne, ale zalecane dla bibliotek)
# Pozwala użytkownikom na instalację biblioteki do systemu (np. /usr/local/include)
install(TARGETS slk_defs1 EXPORT slk_defs1_export)
install(DIRECTORY include/
DESTINATION include
)
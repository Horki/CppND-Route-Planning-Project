#include <io2d.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "render.h"
#include "route_model.h"
#include "route_planner.h"

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path) {
  std::ifstream is{path, std::ios::binary | std::ios::ate};
  if (!is) {
    return std::nullopt;
  }

  auto size = is.tellg();
  std::vector<std::byte> contents(size);

  is.seekg(0);
  is.read((char *)contents.data(), size);

  if (contents.empty()) {
    return std::nullopt;
  }
  return std::move(contents);
}

static void check_range(std::string_view s, float &point) {
  std::cout << s;
  std::cin >> point;
  if (point < 0 || point > 100.0) {
    std::cout << "Invalid range, try again\n";
    check_range(s, point);
  }
}

int main(int argc, const char **argv) {
  std::string osm_data_file = "";
  if (argc == 1) {
    std::cerr << "Usage: [executable] [-f filename.osm]" << std::endl;
    return EXIT_FAILURE;
  }

  for (int i = 1; i < argc; ++i) {
    if (std::string_view{argv[i]} == "-f" && ++i < argc) {
      osm_data_file = argv[i];
    }
  }

  std::vector<std::byte> osm_data;

  if (osm_data.empty() && !osm_data_file.empty()) {
    std::cout << "Reading OpenStreetMap data from the following file: "
              << osm_data_file << std::endl;
    auto data = ReadFile(osm_data_file);
    if (!data) {
      std::cerr << "Failed to read." << std::endl;
      return EXIT_FAILURE;
    }
    osm_data = std::move(*data);
  }

  // Declared floats `start_x`, `start_y`, `end_x`, and `end_y` and get
  // user input for these values using std::cin. Pass the user input to the
  // RoutePlanner object below.
  float start_x, start_y, end_x, end_y;
  std::cout << "The map coordinates begin at (0, 0) in the lower left corner, "
               "and end at (100, 100) in the upper right corner.\n";
  std::cout << "example Start(10, 10), End(90, 90)" << std::endl;
  check_range("Enter a start x between 0 and 100: ", start_x);
  check_range("Enter a start y between 0 and 100: ", start_y);
  check_range("Enter a end   x between 0 and 100: ", end_x);
  check_range("Enter a end   y between 0 and 100: ", end_y);

  std::cout << "Start (" << start_x << ", " << start_y << ") End (" << end_x
            << ", " << end_y << ")\n";

  // Build Model.
  RouteModel model{osm_data};

  // Perform search and render results.
  RoutePlanner route_planner{model, start_x, start_y, end_x, end_y};
  route_planner.AStarSearch();
  std::cout << "Distance: " << route_planner.GetDistance() << " meters.\n";
  Render render{model};

  auto display = io2d::output_surface{400,
                                      400,
                                      io2d::format::argb32,
                                      io2d::scaling::none,
                                      io2d::refresh_style::fixed,
                                      30};
  display.size_change_callback([](io2d::output_surface &surface) {
    surface.dimensions(surface.display_dimensions());
  });
  display.draw_callback(
      [&](io2d::output_surface &surface) { render.Display(surface); });
  display.begin_show();
}

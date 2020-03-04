#ifndef TEST_HPP_
#define TEST_HPP_

#include <string>
#include <optional>
#include <fstream>
#include <vector>
#include <iostream>

#include <gtest/gtest.h>

#include "route_model.h"
#include "route_planner.h"

static std::optional<std::vector<std::byte>> ReadFile(const std::string &);
std::vector<std::byte> ReadOSMData(const std::string &);

class RouteModelTest : public ::testing::Test {
protected:
    std::string osm_data_file = "../data/map.osm";
    std::vector<std::byte> osm_data = ReadOSMData(osm_data_file);
    RouteModel model{osm_data};
};

class RoutePlannerTest : public ::testing::Test {
protected:
    std::string osm_data_file = "../data/map.osm";
    std::vector<std::byte> osm_data = ReadOSMData(osm_data_file);
    RouteModel model{osm_data};
    RoutePlanner route_planner{model, 10, 10, 90, 90};

    // Construct start_node and end_node as in the model.
    float start_x = 0.1;
    float start_y = 0.1;
    float end_x = 0.9;
    float end_y = 0.9;
    RouteModel::Node* start_node = &model.FindClosestNode(start_x, start_y);
    RouteModel::Node* end_node = &model.FindClosestNode(end_x, end_y);
};


static std::optional<std::vector<std::byte>> ReadFile(const std::string &path) {
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if (!is) {
        return std::nullopt;
    }

    auto size = is.tellg();
    std::vector<std::byte> contents(size);

    is.seekg(0);
    is.read((char*)contents.data(), size);

    if (contents.empty()) {
        return std::nullopt;
    }
    return std::move(contents);
}

std::vector<std::byte> ReadOSMData(const std::string &path) {
    std::vector<std::byte> osm_data;
    auto data = ReadFile(path);
    if (!data) {
        std::cerr << "Failed to read OSM data." << std::endl;
    } else {
        osm_data = std::move(*data);
    }
    return osm_data;
}

#endif
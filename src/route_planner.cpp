#include "route_planner.h"

#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y,
                           float end_x, float end_y)
    : m_Model(model) {
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;
  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);
}

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(
    RouteModel::Node *current_node) {
  distance = 0.0f;
  std::vector<RouteModel::Node> path_found;
  RouteModel::Node parent;
  while (current_node->parent != nullptr) {
    path_found.push_back(*current_node);
    parent = *(current_node->parent);
    distance += current_node->distance(parent);
    current_node = current_node->parent;
  }
  path_found.push_back(*current_node);
  distance *= m_Model.MetricScale();

  return path_found;
}

void RoutePlanner::AStarSearch() {
  start_node->visited = true;

  open_list.push_back(start_node);
  RouteModel::Node *current_node = nullptr;
  while (open_list.size() > 0) {
    current_node = NextNode();
    if (current_node->distance(*end_node) == 0) {
      m_Model.path = ConstructFinalPath(current_node);
      return;
    }
    AddNeighbors(current_node);
  }
}

float RoutePlanner::CalculateHValue(const RouteModel::Node *node) {
  return node->distance(*end_node);
}

RouteModel::Node *RoutePlanner::NextNode() {
  std::sort(open_list.begin(), open_list.end(),
            [](const auto &first, const auto &second) {
              return first->h_value + first->g_value <
                     second->h_value + second->g_value;
            });
  RouteModel::Node *lowest_node = open_list.front();
  open_list.erase(open_list.begin());
  return lowest_node;
}

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
  current_node->FindNeighbors();
  for (auto neighbour : current_node->neighbors) {
    neighbour->parent = current_node;
    neighbour->g_value =
        current_node->g_value + current_node->distance(*neighbour);
    neighbour->h_value = CalculateHValue(neighbour);

    open_list.push_back(neighbour);
    neighbour->visited = true;
  }
}
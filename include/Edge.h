#pragma once

#include "Coordinate.h"
#include "AxialDirection.h"
#include "common.h"

class Edge {
    public:
        Edge(Coordinate2D c, HexDirection d);
        static const std::array<HexDirection, 6> directions;

        /**
         * @brief Get the index of an edge in the directions array
         *
         * @param d Direction of the edge
         * @return const int The index of the edge in the directions array
         */
        static const int getEdgeIndex(HexDirection d);

        /**
         * @brief Get all representations of a given edge
         *
         * @param d
         * @return std::array<HexPath, 3>
         */
        static std::array<HexPath, 2>
        getAllEdgeRepresentations(HexDirection d);

        /**
         * @brief Get representations of all adjacent edges. The two "local" edges first 
         * and then both representations of the first "distant" edge, and then the second edge
         * 
         */
        static std::array<HexPath, 6>
        getAdjacentEdges(HexDirection d);

        /**
         * @brief Get the directions of the adjacent local edges \p d
         *
         * @param d The direction of the target edge
         * @return std::array<Direction, 2> The two edges which are adjacent to the
         * target edge
         */
        static std::array<HexPath, 2>
        getLocalAdjacentEdges(HexDirection d);

        /**
         * @brief Get all representations of the two adjacent edges  \p d that must be
         * traversed to. There are two distant edges, and two methods of travel for
         * each edge
         *
         * @param d The direction of the target edge
         * @return std::array<HexPath, 4>
         */
        static std::array<HexPath, 4>
        getDistantAdjacentEdges(HexDirection d);

    private:
        Coordinate2D coordinate;
        HexDirection direction;
};
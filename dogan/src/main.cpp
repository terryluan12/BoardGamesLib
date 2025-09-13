#include "AxialDirection.h"
#include "Config.h"
#include "DoganConfigBuilder.h"
#include "DoganGame.h"
#include "Vertex.h"
#include "enums.h"
// #include <benchmark/benchmark.h>

using namespace Dogan;
int main() {}

// static void BM_INITIALIZE_GAME(benchmark::State &state) {
//   auto config = Dogan::ConfigBuilder().build();
//   for (auto _ : state) {
//     Dogan::Game game(config);
//   }
// }
// static void BM_ADD_PLAYER(benchmark::State &state) {
//   auto config = Dogan::ConfigBuilder().build();
//   for (auto _ : state) {
//     Dogan::Game game(config);
//     game.addPlayer(0);
//   }
// }
// static void BM_BUILD_BUILDING(benchmark::State &state) {
//   auto config = Dogan::ConfigBuilder().build();
//   for (auto _ : state) {
//     Dogan::Game game(config);
//     game.addPlayer(0);
//     game.buildStructure(0, Dogan::StructureType::VILLAGE, {0, 0},
//                         Dogan::Direction::NORTH, {0, 0, 0, 0, 0}, false);
//   }
// }
// static void BM_ADD_ADJACENT_BUILDING(benchmark::State &state) {
//   auto config = Dogan::ConfigBuilder().build();
//   for (auto _ : state) {

//     Dogan::Game game(config);
//     game.addPlayer(0);
//     game.buildStructure(0, Dogan::StructureType::VILLAGE, {0, 0},
//                         Dogan::Direction::NORTH, {0, 0, 0, 0, 0}, false);
//     game.buildStructure(0, Dogan::StructureType::ROAD, {0, 0},
//                         Dogan::Direction::NORTHWEST, {0, 0, 0, 0, 0}, false);
//     game.buildStructure(0, Dogan::StructureType::ROAD, {0, 0},
//                         Dogan::Direction::WEST, {0, 0, 0, 0, 0}, false);
//     game.buildStructure(0, Dogan::StructureType::VILLAGE, {0, 0},
//                         Dogan::Direction::SOUTHWEST, {0, 0, 0, 0, 0});
//   }
// }
// BENCHMARK(BM_INITIALIZE_GAME);
// BENCHMARK(BM_ADD_PLAYER);
// BENCHMARK(BM_BUILD_BUILDING);
// // BENCHMARK(BM_ADD_ADJACENT_BUILDING);

// BENCHMARK_MAIN();
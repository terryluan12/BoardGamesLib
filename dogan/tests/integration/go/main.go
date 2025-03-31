package main

import (
	"fmt"
	"log"

	"github.com/terryluan12/BoardGames/dogan/extras/go/dogan"
)


func main() {
	log.Println("Start Test")

	config := dogan.NewConfigBuilder()
	defer dogan.DeleteConfigBuilder(config)
	config.SetRobberLocation(dogan.NewCoordinate2D(0, 0))
	if response := config.Validate(false); response.GetSucceeded() {
		panic("Error: Validate should return false")
	}
	coordinate_0_2 := dogan.NewCoordinate2D(0, 2)
	defer dogan.DeleteCoordinate2D(coordinate_0_2)
	coordinate_3_3 := dogan.NewCoordinate2D(3, 3)
	defer dogan.DeleteCoordinate2D(coordinate_3_3)
	tileLocations := []dogan.Coordinate2D{&coordinate_0_2, &coordinate_3_3}
	config.SetTileLocations(tileLocations)

	config.Build()

	game := dogan.NewGame(config, false)

	game.AddPlayer(0)
	tenArrays := dogan.NewIntArray5()
	tenArrays.Fill(10)
	zeroArrays := dogan.NewIntArray5()
	zeroArrays.Fill(0)
	game.GiveResources(0, tenArrays)

	coord := dogan.NewCoordinate2D(0, 0)

	game.BuildStructure(0, dogan.DoganStructureTypeType_VILLAGE, coord, dogan.AxialDirectionDirection_NORTH, zeroArrays, false)
	for resourceCount, i := game.GetResourceCount(0), 0; i < int(resourceCount.Size()); i++ {
		fmt.Printf("There are %d of resource %d for player 0\n", resourceCount.Get(i), i)
	}
}
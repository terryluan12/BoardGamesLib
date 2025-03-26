package main

import (
	"fmt"
	"log"

	"github.com/terryluan12/BoardGames/dogan/extras/go/dogan"
)


func main() {
	log.Println("Start Test")

	config := dogan.NewConfigBuilder().Build()

	game := dogan.NewGame(config)

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
open Jest;
open Expect;
open Types;

describe("Types", () => {
  describe("Coordinate", () => {
    describe("isvalid", () => {
      let latitudeBoundaries = {
        max: 90.->Coordinate.latitude_from_float,
        min: (-90.)->Coordinate.latitude_from_float,
      };

      let longitudeBoundaries = {
        max: 180.->Coordinate.longitude_from_float,
        min: (-180.)->Coordinate.longitude_from_float,
      };

      let boundaryBox = { longitudeBoundaries, latitudeBoundaries };

      let assertIsValid = (coordinate, result) => {
        expect(
          Coordinate.isValid(
            boundaryBox,
            coordinate,
          ),
        )
        |> toEqual(result);
      };

      test(
        "Gives false when longitudeBoundaries max is above coordinate longitude",
        () => {
        assertIsValid(
          (
            200.->Coordinate.longitude_from_float,
            0.->Coordinate.latitude_from_float,
            0.->Coordinate.altitude_from_float,
          ),
          false,
        )
      });

      test(
        "Gives false when longitudeBoundaries min is below coordinate longitude",
        () => {
        assertIsValid(
          (
            (-219.)->Coordinate.longitude_from_float,
            0.->Coordinate.latitude_from_float,
            0.->Coordinate.altitude_from_float,
          ),
          false,
        )
      });

      test(
        "Gives false when latitudeBoundaries max is above coordinate latitude",
        () => {
        assertIsValid(
          (
            0.->Coordinate.longitude_from_float,
            99.->Coordinate.latitude_from_float,
            0.->Coordinate.altitude_from_float,
          ),
          false,
        )
      });

      test(
        "Gives false when latitudeBoundaries min is below coordinate latitude",
        () => {
        assertIsValid(
          (
            0.->Coordinate.longitude_from_float,
            (-99.)->Coordinate.latitude_from_float,
            0.->Coordinate.altitude_from_float,
          ),
          false,
        )
      });

      test(
        "Gives true when coordinate latitude is between boundaries latitude min and max and coordinate longitude is between boudaries longitude min and max",
        () => {
        assertIsValid(
          (
            12.->Coordinate.longitude_from_float,
            (-42.)->Coordinate.latitude_from_float,
            0.->Coordinate.altitude_from_float,
          ),
          true,
        )
      });
    })
  })
});

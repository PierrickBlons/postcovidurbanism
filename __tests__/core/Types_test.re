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

      test(
        "Gives false when longitudeBoundaries max is above coordinate longitude",
        () => {
        expect(
          Coordinate.isValid(
            longitudeBoundaries,
            latitudeBoundaries,
            (
              200.->Coordinate.longitude_from_float,
              0.->Coordinate.latitude_from_float,
              0.->Coordinate.altitude_from_float,
            ),
          ),
        )
        |> toEqual(false)
      });

      test(
        "Gives false when longitudeBoundaries min is below coordinate longitude",
        () => {
        expect(
          Coordinate.isValid(
            longitudeBoundaries,
            latitudeBoundaries,
            (
              (-219.)->Coordinate.longitude_from_float,
              0.->Coordinate.latitude_from_float,
              0.->Coordinate.altitude_from_float,
            ),
          ),
        )
        |> toEqual(false)
      });

      test(
        "Gives false when latitudeBoundaries max is above coordinate latitude",
        () => {
        expect(
          Coordinate.isValid(
            longitudeBoundaries,
            latitudeBoundaries,
            (
              0.->Coordinate.longitude_from_float,
              99.->Coordinate.latitude_from_float,
              0.->Coordinate.altitude_from_float,
            ),
          ),
        )
        |> toEqual(false)
      });

      test(
        "Gives false when latitudeBoundaries min is below coordinate latitude",
        () => {
        expect(
          Coordinate.isValid(
            longitudeBoundaries,
            latitudeBoundaries,
            (
              0.->Coordinate.longitude_from_float,
              (-99.)->Coordinate.latitude_from_float,
              0.->Coordinate.altitude_from_float,
            ),
          ),
        )
        |> toEqual(false)
      });
    })
  })
});

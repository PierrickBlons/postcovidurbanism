open Jest;
open Expect;
open Types;

describe("Types", () => {
  describe("Coordinate", () => {
    describe("isWithinBox", () => {
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
          Coordinate.isWithinBox(
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
    });

    describe("isWithinLatitudeBoundaries", () => {
      let someBoundaries = {
        max: 90.->Coordinate.latitude_from_float,
        min: (-90.)->Coordinate.latitude_from_float,
      };

      let assertIsWithinLatitudeBoundaries = (latitude, result) => {
        expect(Coordinate.isWithinLatitudeBoundaries(someBoundaries, latitude->Coordinate.latitude_from_float)) 
        |> toEqual(result);
      };

      test("Gives false when latitude is below boundaries min", () => {
        assertIsWithinLatitudeBoundaries(-100., false);
      });

      test("Gives false when latitude is above boundaries max", () => {
        assertIsWithinLatitudeBoundaries(100., false);
      });

      test("Gives true when latitude is above boundaries min", () => {
        assertIsWithinLatitudeBoundaries(10., true);
      });

      test("Gives true when latitude is below boundaries max", () => {
        assertIsWithinLatitudeBoundaries(80., true);
      });
    });

    describe("isWithinLongitudeBoundaries", () => {
      let someLongitudeBoundaries = {
        max: 90.->Coordinate.longitude_from_float,
        min: (-90.)->Coordinate.longitude_from_float,
      };

      let assertIsWithinLongitudeBoundaries = (longitude, result) => {
        expect(Coordinate.isWithinLongitudeBoundaries(someLongitudeBoundaries, longitude->Coordinate.longitude_from_float)) 
        |> toEqual(result);
      };

      test("Gives false when longitude is below boundaries min", () => {
        assertIsWithinLongitudeBoundaries(-100., false);
      });

      test("Gives false when longitude is above boundaries max", () => {
        assertIsWithinLongitudeBoundaries(100., false);
      });

      test("Gives true when longitude is above boundaries min", () => {
        assertIsWithinLongitudeBoundaries(10., true);
      });

      test("Gives true when longitude is below boundaries max", () => {
        assertIsWithinLongitudeBoundaries(80., true);
      });
    });
  });
});

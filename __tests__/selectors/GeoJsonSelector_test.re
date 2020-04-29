open Jest;
open Expect;

describe("GeoJsonSelector", () => {
  describe("toCoordinates", () => {
    let value1 = 123;
    let value2 = "234";

    test("When (None, Some)", () => {
      expect(GeoJsonSelector.toCoordinates((None, Some(value2))))
      |> toEqual(None)
    });

    test("When (Some, None)", () => {
      expect(GeoJsonSelector.toCoordinates((Some(value1), None)))
      |> toEqual(None)
    });

    test("When (None, None)", () => {
      expect(GeoJsonSelector.toCoordinates((None, None))) |> toEqual(None)
    });

    test("When (Some, Some)", () => {
      let value1 = 123;
      let value2 = "234";
      expect(GeoJsonSelector.toCoordinates((Some(value1), Some(value2))))
      |> toEqual(
           Some((value1, value2, Types.Coordinate.altitude_from_float(0.))),
         );
    });
  });
  describe("makeProperties", () => {
    test("With no optional props", () => {
      expect(
        GeoJsonSelector.makeProperties(
          ~kind="kind",
          ~description=None,
          ~author=None,
          ~title="title",
        ),
      )
      |> toMatchSnapshot
    })
  });
});
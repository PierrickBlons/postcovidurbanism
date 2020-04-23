open DeckGl.Layers.Line;

let initialViewState: DeckGl.viewport = {
  longitude: 1.091269,
  latitude: 49.443268,
  zoom: 10,
  pitch: 0,
  bearing: 0,
};

let layerLineId = "layer-id";
let lineWidth: int = 7;
let linePedestrianColor: (int, int, int, int) = (36, 142, 128, 255);
let lineCyclingColor: (int, int, int, int) = (0, 128, 255, 200);
let lineSchoolColor: (int, int, int, int) = (255, 191, 0, 255);

let getColor = kind =>
  switch (kind) {
  | "pieton" => linePedestrianColor
  | "velo" => lineCyclingColor
  | "ecole" => lineSchoolColor
  | _ => (0, 0, 0, 0)
  };

type state = {
  label: string,
  visible: bool,
  description: string,
  authorName: string,
  authorLink: string,
};

// type action =
//   | Click(info);

let initialState = {
  label: "Urbanisme tactique post covid",
  description: {j|Sélectionner un élément de la cartographie pour faire apparaitre le détail de la proposition|j},
  visible: true,
  authorName: "",
  authorLink: "",
};

[@react.component]
let make = () => {
  // let (proposals, _) = Queries.useProposalsListQuery();

  // let (state, dispatch) =
  //   React.useReducer(
  //     (_, action) =>
  //       switch (action) {
  //       | Click(info) => {
  //           label: info.detail.label,
  //           description: info.detail.description,
  //           visible: true,
  //           authorName: info.detail.authorName,
  //           authorLink: info.detail.authorLink,
  //         }
  //       },
  //     initialState,
  //   );

  // let data =
  //   switch (proposals) {
  //   | Data(data) =>
  //     data##proposal
  //     ->Belt.Array.map(proposal => {
  //         switch (
  //           proposal##startLatitude,
  //           proposal##startLongitude,
  //           proposal##endLatitude,
  //           proposal##endLongitude,
  //         ) {
  //         | (
  //             Some(startLatitude),
  //             Some(startLongitude),
  //             Some(endLatitude),
  //             Some(endLongitude),
  //           ) => {
  //             label: proposal##title,
  //             kind: proposal##kind,
  //             authorName:
  //               proposal##author
  //               ->Belt.Option.mapWithDefault("", author => author##name),
  //             authorLink:
  //               proposal##author
  //               ->Belt.Option.mapWithDefault("", author => author##link->Belt.Option.getWithDefault("")),
  //             description:
  //               proposal##description->Belt.Option.getWithDefault(""),
  //             sourcePosition: (
  //               Js.Json.decodeNumber(startLongitude)
  //               ->Belt.Option.getWithDefault(0.),
  //               Js.Json.decodeNumber(startLatitude)
  //               ->Belt.Option.getWithDefault(0.),
  //             ),
  //             targetPosition: (
  //               Js.Json.decodeNumber(endLongitude)
  //               ->Belt.Option.getWithDefault(0.),
  //               Js.Json.decodeNumber(endLatitude)
  //               ->Belt.Option.getWithDefault(0.),
  //             ),
  //           }
  //         | _ => {
  //             label: "",
  //             kind: "",
  //             description: "",
  //             authorName: "",
  //             authorLink: "",
  //             sourcePosition: (0., 0.),
  //             targetPosition: (0., 0.),
  //           }
  //         }
  //       })
  //   | _ => [||]
  //   };

  // let data: geojson = {
  //   _type: "FeatureCollection",
  //   version: "draft",
  //   features: [|
  //     {
  //       _type: "Feature",
  //       geometry: {
  //         _type: "LineString",
  //         coordinates: [| 
  //           [|1.07656,49.43435,0.|],
  //           [|1.07729,49.43396,0.|],
  //           [|1.07759,49.4338,0.|],
  //           [|1.07765,49.43378,0.|],
  //           [|1.07773,49.43377,0.|],
  //           [|1.07786,49.43369,0.|],
  //           [|1.07796,49.43362,0.|],
  //           [|1.07807,49.43354,0.|],
  //           [|1.07804,49.43349,0.|],
  //           [|1.07803,49.43348,0.|],
  //           [|1.07803,49.43344,0.|],
  //           [|1.07804,49.43341,0.|],
  //           [|1.07805,49.43339,0.|],
  //           [|1.07819,49.43324,0.|],
  //           [|1.0782,49.43321,0.|],
  //           [|1.07833,49.433,0.|],
  //           [|1.07845,49.43277,0.|],
  //           [|1.07854,49.43262,0.|],
  //           [|1.07858,49.43257,0.|],
  //           [|1.0786,49.43256,0.|],
  //           [|1.07862,49.43255,0.|],
  //           [|1.07869,49.43253,0.|],
  //           [|1.07875,49.43232,0.|],
  //           [|1.07878,49.43212,0.|],
  //           [|1.0788,49.43192,0.|],
  //           [|1.0788,49.4317,0.|],
  //           [|1.07879,49.43153,0.|],
  //           [|1.07879,49.43143,0.|],
  //           [|1.07877,49.43127,0.|],
  //           [|1.07875,49.43109,0.|],
  //           [|1.07874,49.43094,0.|],
  //           [|1.07871,49.43071,0.|],
  //           [|1.0787,49.4307,0.|],
  //           [|1.07869,49.43069,0.|],
  //           [|1.07869,49.43068,0.|],
  //           [|1.07868,49.43067,0.|],
  //           [|1.07868,49.43066,0.|],
  //           [|1.07868,49.43065,0.|],
  //           [|1.07868,49.43064,0.|],
  //           [|1.07868,49.43063,0.|],
  //           [|1.07868,49.43061,0.|],
  //           [|1.07868,49.4306,0.|],
  //           [|1.07869,49.43059,0.|],
  //           [|1.07869,49.43058,0.|],
  //           [|1.0787,49.43057,0.|],
  //           [|1.07871,49.43056,0.|],
  //           [|1.07872,49.43055,0.|],
  //           [|1.07873,49.43054,0.|],
  //           [|1.07874,49.43053,0.|],
  //           [|1.07875,49.43052,0.|],
  //           [|1.07876,49.43051,0.|],
  //           [|1.07878,49.4305,0.|],
  //           [|1.07881,49.43043,0.|],
  //           [|1.07882,49.43038,0.|],
  //           [|1.07886,49.4303,0.|],
  //           [|1.07892,49.43015,0.|],
  //           [|1.079,49.43001,0.|],
  //           [|1.07906,49.4299,0.|],
  //           [|1.0791,49.4298,0.|],
  //           [|1.07915,49.4297,0.|],
  //           [|1.07922,49.42961,0.|],
  //           [|1.0793,49.42951,0.|],
  //           [|1.07938,49.42941,0.|],
  //           [|1.07951,49.42929,0.|],
  //           [|1.07964,49.42916,0.|],
  //           [|1.07977,49.42906,0.|],
  //           [|1.07992,49.42895,0.|],
  //           [|1.08002,49.42888,0.|],
  //           [|1.08009,49.42884,0.|],
  //           [|1.08107,49.42819,0.|],
  //           [|1.08158,49.42787,0.|],
  //           [|1.08181,49.42774,0.|],
  //           [|1.08203,49.42764,0.|],
  //           [|1.08228,49.42754,0.|],
  //           [|1.08262,49.42741,0.|],
  //           [|1.08353,49.42709,0.|],
  //           [|1.08451,49.42676,0.|],
  //           [|1.08572,49.42634,0.|],
  //           [|1.08648,49.42609,0.|],
  //           [|1.08661,49.42605,0.|],
  //           [|1.08672,49.42602,0.|],
  //           [|1.08683,49.426,0.|],
  //         |]
  //       }
  //     }
  //   |]
  // };

  let json = {js|{
    "type": "FeatureCollection",
    "version": "draft",
    "features": [
        {
            "type": "Feature",
            "geometry": {
                "type": "LineString",
                "coordinates": [
                    [1.07656,49.43435,0],
                    [1.07729,49.43396,0],
                    [1.07759,49.4338,0],
                    [1.07765,49.43378,0],
                    [1.07773,49.43377,0],
                    [1.07786,49.43369,0],
                    [1.07796,49.43362,0],
                    [1.07807,49.43354,0],
                    [1.07804,49.43349,0],
                    [1.07803,49.43348,0],
                    [1.07803,49.43344,0],
                    [1.07804,49.43341,0],
                    [1.07805,49.43339,0],
                    [1.07819,49.43324,0],
                    [1.0782,49.43321,0],
                    [1.07833,49.433,0],
                    [1.07845,49.43277,0],
                    [1.07854,49.43262,0],
                    [1.07858,49.43257,0],
                    [1.0786,49.43256,0],
                    [1.07862,49.43255,0],
                    [1.07869,49.43253,0],
                    [1.07875,49.43232,0],
                    [1.07878,49.43212,0],
                    [1.0788,49.43192,0],
                    [1.0788,49.4317,0],
                    [1.07879,49.43153,0],
                    [1.07879,49.43143,0],
                    [1.07877,49.43127,0],
                    [1.07875,49.43109,0],
                    [1.07874,49.43094,0],
                    [1.07871,49.43071,0],
                    [1.0787,49.4307,0],
                    [1.07869,49.43069,0],
                    [1.07869,49.43068,0],
                    [1.07868,49.43067,0],
                    [1.07868,49.43066,0],
                    [1.07868,49.43065,0],
                    [1.07868,49.43064,0],
                    [1.07868,49.43063,0],
                    [1.07868,49.43061,0],
                    [1.07868,49.4306,0],
                    [1.07869,49.43059,0],
                    [1.07869,49.43058,0],
                    [1.0787,49.43057,0],
                    [1.07871,49.43056,0],
                    [1.07872,49.43055,0],
                    [1.07873,49.43054,0],
                    [1.07874,49.43053,0],
                    [1.07875,49.43052,0],
                    [1.07876,49.43051,0],
                    [1.07878,49.4305,0],
                    [1.07881,49.43043,0],
                    [1.07882,49.43038,0],
                    [1.07886,49.4303,0],
                    [1.07892,49.43015,0],
                    [1.079,49.43001,0],
                    [1.07906,49.4299,0],
                    [1.0791,49.4298,0],
                    [1.07915,49.4297,0],
                    [1.07922,49.42961,0],
                    [1.0793,49.42951,0],
                    [1.07938,49.42941,0],
                    [1.07951,49.42929,0],
                    [1.07964,49.42916,0],
                    [1.07977,49.42906,0],
                    [1.07992,49.42895,0],
                    [1.08002,49.42888,0],
                    [1.08009,49.42884,0],
                    [1.08107,49.42819,0],
                    [1.08158,49.42787,0],
                    [1.08181,49.42774,0],
                    [1.08203,49.42764,0],
                    [1.08228,49.42754,0],
                    [1.08262,49.42741,0],
                    [1.08353,49.42709,0],
                    [1.08451,49.42676,0],
                    [1.08572,49.42634,0],
                    [1.08648,49.42609,0],
                    [1.08661,49.42605,0],
                    [1.08672,49.42602,0],
                    [1.08683,49.426,0]
                    ]
            },
            "properties": {
                "label": "Rue Jeanne d'Arc 76000 Rouen",
                "score": 0.9600175493234017,
                "id": "76540_4460",
                "type": "street",
                "x": 561333.12,
                "y": 6928332.89,
                "importance": 0.560193042557419,
                "name": "Rue Jeanne d'Arc",
                "postcode": "76000",
                "citycode": "76540",
                "city": "Rouen",
                "context": "76, Seine-Maritime, Normandie"
            }
        },
        {
            "type": "Feature",
            "geometry": {
                "type": "Point",
                "coordinates": [
                    1.071914,
                    49.856201
                ]
            },
            "properties": {
                "label": "Route de Rouen 76550 Tourville-sur-Arques",
                "score": 0.2823329272622731,
                "id": "76707_0016",
                "type": "street",
                "x": 561258.32,
                "y": 6974740.86,
                "importance": 0.3364314306542351,
                "name": "Route de Rouen",
                "postcode": "76550",
                "citycode": "76707",
                "city": "Tourville-sur-Arques",
                "context": "76, Seine-Maritime, Normandie"
            }
        }
    ],
    "attribution": "BAN",
    "licence": "ETALAB-2.0",
    "query": "rue-jeanne-d'arc-rouen",
    "limit": 5
}
|js};

let data = Js.Json.parseExn(json);

  let layers = [|
    create({
      id: layerLineId,
      data,
      getLineColor: d => getColor("velo"),
      pickable: true,
    }),
  |];

  <DeckGl reuseMaps=true initialViewState layers controller=true>
    <DeckGl.StaticMap
      viewState=initialViewState
      mapStyle="mapbox://styles/mapbox/dark-v10"
      mapboxApiAccessToken=Env.mapbox_token_api
    />
    // <Tooltip
    //   isVisible={state.visible}
    //   label={state.label}
    //   description={state.description}
    //   authorName={state.authorName}
    //   authorLink={state.authorLink}
    // />
  </DeckGl>;
};

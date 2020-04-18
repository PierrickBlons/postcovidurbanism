let initialViewState: DeckGl.viewport = {
  longitude: 1.091269,
  latitude: 49.443268,
  zoom: 13,
  pitch: 0,
  bearing: 0,
};

let data: array(DeckGl.Layers.Line.data) = [|
  {
    sourcePosition: (1.0887587, 49.4391237),
    targetPosition: (1.092123, 49.4446816),
  },
|];

let layerLineId = "layer-id";
let lineColor: list(int) = [255, 0, 0];
let lineWidth: int = 3;

[@react.component]
let make = () => {
  let layers = [|DeckGl.Layers.Line.create({
    id: layerLineId, 
    data, 
    getColor: lineColor, 
    getWidth: lineWidth,
    }),
  |];
  <DeckGl reuseMaps=true initialViewState layers controller=true>
    <DeckGl.StaticMap
      viewState=initialViewState
      mapStyle="mapbox://styles/mapbox/light-v10"
      mapboxApiAccessToken=Env.mapbox_token_api
    />
  </DeckGl>;
};

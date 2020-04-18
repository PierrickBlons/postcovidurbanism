let initialViewState: DeckGl.viewport = {
  longitude: (-122.41669),
  latitude: 37.7853,
  zoom: 13,
  pitch: 0,
  bearing: 0,
};

let data: array(DeckGl.Layers.Line.data) = [|
  {
    sourcePosition: ((-122.41669), 37.7853),
    targetPosition: ((-122.41669), 37.781),
  },
|];

let layerLineId = "layer-id";

[@react.component]
let make = () => {
  let layers = [|DeckGl.Layers.Line.create({id: layerLineId, data})|];
  <DeckGl reuseMaps=true initialViewState layers controller=true>
    <DeckGl.StaticMap
      viewState=initialViewState
      mapStyle="mapbox://styles/mapbox/light-v9"
      mapboxApiAccessToken="pk.eyJ1IjoicGllcnJpY2tibCIsImEiOiJjazRhMjBkcXQwMmhsM2VwMXkyM3JyZW54In0.qv1Lq36PUGxriIIbLUtovw"
    />
  </DeckGl>;
};

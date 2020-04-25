open ApolloHooks;
open Types;

module Extract = {
  let optionalFloat = someFloat =>
    someFloat->Belt.Option.flatMap(Js.Json.decodeNumber);
  let path = path =>
    path
    ->Belt.Option.map(DeckGl.Layers.GeoJson.geometry_decode)
    ->Belt.Option.flatMap(Utils.resultToOption);
};

module GetProposalsListQuery = [%graphql
  {|
    query GetProposalsList {
            proposal @bsRecord {
                title
                startLatitude @bsDecoder(fn: "Extract.optionalFloat")
                startLongitude @bsDecoder(fn: "Extract.optionalFloat")
                endLatitude @bsDecoder(fn: "Extract.optionalFloat")

                endLongitude @bsDecoder(fn: "Extract.optionalFloat")
                description
                kind
                path @bsDecoder(fn: "Extract.path")
                author @bsRecord {
                    name
                    link
                }
            }
        }
    |}
];

let useProposalsListQuery = () => useQuery(GetProposalsListQuery.definition);

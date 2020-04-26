open ApolloHooks;
open Types;

module Extract = {
  let optionalLatitude = someFloat =>
    someFloat
    ->Belt.Option.map(Coordonate.latitude_decode)
    ->Belt.Option.flatMap(Utils.resultToOption);
  let optionalLongitude = someFloat =>
    someFloat
    ->Belt.Option.map(Coordonate.longitude_decode)
    ->Belt.Option.flatMap(Utils.resultToOption);
  let path = path =>
    path
    ->Belt.Option.map(geometry_decode)
    ->Belt.Option.flatMap(Utils.resultToOption);
};

module GetProposalsListQuery = [%graphql
  {|
    query GetProposalsList {
            proposal @bsRecord {
                title
                startLatitude @bsDecoder(fn:
                                         "Extract.optionalLatitude")
                startLongitude @bsDecoder(fn:
                                         "Extract.optionalLongitude")
                endLatitude @bsDecoder(fn:
                                         "Extract.optionalLatitude")

                endLongitude @bsDecoder(fn:
                                         "Extract.optionalLongitude")
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

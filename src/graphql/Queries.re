
open ApolloHooks;

module GetProposalsListQuery = [%graphql {|
    query GetProposalsList { 
            proposal {
                title
                startLatitude
                startLongitude
                endLatitude
                endLongitude
                description
                kind
            }
        }
    |}
];

let useProposalsListQuery = () => useQuery(GetProposalsListQuery.definition);
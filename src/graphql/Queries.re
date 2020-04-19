
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
            }
        }
    |}
];

let useProposalsListQuery = () => useQuery(GetProposalsListQuery.definition);
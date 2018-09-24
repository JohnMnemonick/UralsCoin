// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers 
// Copyright (c) 2015-2017 The Dash developers 
// Copyright (c) 2015-2017 The Urals developers
// Copyright (c) 2017-2018 The Urals developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 *
 * CBlock(hash=000000000019d6, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=4a5e1e, nTime=1231006505, nBits=1d00ffff, nNonce=2083236893, vtx=1)
 *   CTransaction(hash=4a5e1e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d0104455468652054696d65732030332f4a616e2f32303039204368616e63656c6c6f72206f6e206272696e6b206f66207365636f6e64206261696c6f757420666f722062616e6b73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0x5F1DF16B2B704C8A578D0B)
 *   vMerkleTree: 4a5e1e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "28/06/2017: Russia’s Parliament is Discussing the Legalization of Bitcoin.";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 210000;
        consensus.BIP34Height = 80000;
        consensus.BIP34Hash = uint256S("0x00000000218e189b4268e72f40e2fab3b95995ab2c4cb195eba1f10ad20c122c");
        consensus.BIP65Height = 150000; 
        consensus.BIP66Height = 85000; 
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");//"00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 6 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1; // if we found only one block
        consensus.nMinerConfirmationWindow = 1728; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1525132800; // May 1 2018 @ 0:00am (UTC)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1535760000; // 1 Sep 2018 @ 0:00am (UTC)
	consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nHeight = 80000;

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1535760000; // Aug 1 2018 @ 0:00am (UTC)
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1607990400; // 12/15/2020 @ 12:00am (UTC)
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nHeight = 91500;

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1535760000; // Aug 1 2018 @ 0:00am (UTC)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 1607990400; // 12/15/2020 @ 12:00am (UTC)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nHeight = 92000;

        // The best chain should have at least this much work.
        //consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000fe8df6ab2a54f");
        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000000df6ab2a54f");
        // By default assume that the signatures in ancestors of this block are valid.
        // consensus.defaultAssumeValid = uint256S("0x00000000000000000013176bf8d7dfeab4e1db31dc93bc311b436e82ab226b90"); //453354
        consensus.defaultAssumeValid = uint256S("0x000000001560866c21324eaba656d156965ccc1d05937d85ae189a89f3c98752"); //90000

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xa3;    
        pchMessageStart[1] = 0xd5;    
        pchMessageStart[2] = 0xc2;    
        pchMessageStart[3] = 0xf9;     

/*        pchMessageStart[0] = 0xa4;    
        pchMessageStart[1] = 0xd6;    
        pchMessageStart[2] = 0xc3;    
        pchMessageStart[3] = 0xf0;     
*/

        nDefaultPort = 7444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1504224000, 25912842, 0x1e0ffff0, 1, 100 * COIN);//Time, Nonce,nBits, version, reward
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000bf56638a0f85009007e92cd848160d5211da779fd4e23f4bd22f0f5221a"));
        assert(genesis.hashMerkleRoot == uint256S("0x5bab319403ecce5eccd4715162fd72d35313064211ff16fccde441a12b2b93b8"));
	    

        vFixedSeeds.clear();
        vSeeds.clear();
/*        vSeeds.push_back(CDNSSeedData("162.213.250.203", "162.213.250.203","true"));
        vSeeds.push_back(CDNSSeedData("5.149.254.22", "5.149.254.22"));
        vSeeds.push_back(CDNSSeedData("5.149.254.11", "5.149.254.11"));
        vSeeds.push_back(CDNSSeedData("77.220.215.168", "77.220.215.168"));
*/		
		
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,130);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,5);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,204);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

	strSporkKey = "04fd2acf24b6951e16085650f7cc3cd83e6865ca9bf78e03db37707df047982dfef6a23e628dbf4810aa97e0bed0c7ed98782d71d68184d7ce8ca8de09d0b0f856";
	strMasternodePaymentsPubKey = "04fd2acf24b6951e16085650f7cc3cd83e6865ca9bf78e03db37707df047982dfef6a23e628dbf4810aa97e0bed0c7ed98782d71d68184d7ce8ca8de09d0b0f856";
	
        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of 
	(  0, uint256S("0x00000bf56638a0f85009007e92cd848160d5211da779fd4e23f4bd22f0f5221a"))
        };

        chainTxData = ChainTxData{
            // Data as of block 000000002a1ad90c0aa8f9c40b96fd7ffc288ce04a37135085be1abc750184e2 (height 118288).
            1536039390, // * UNIX timestamp of last known number of transactions
            181575,  // * total number of transactions between genesis and that timestamp
                        //   (the tx=... number in the SetBestChain debug.log lines)
            10.0         // * estimated number of transactions per second after that timestamp
        };
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 210000;
        //consensus.BIP34Height = 21111;
        consensus.BIP34Height = 600;
        consensus.BIP34Hash = uint256S("0x000006521af2fa46fef634f70a077bd30f61555692f4132ad1417ba6bff58688");
        consensus.BIP65Height = 850; 
        consensus.BIP66Height = 750;
        //consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");//"00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit = uint256S("0fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");//"00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        //consensus.fPowNoRetargeting = false;
        consensus.fPowNoRetargeting = true;
        //consensus.nRuleChangeActivationThreshold = 1512;
        consensus.nRuleChangeActivationThreshold = 108;
        //consensus.nMinerConfirmationWindow = 2016;
        consensus.nMinerConfirmationWindow = 144;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1526342400; // May 15, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1567296000; //Sep 1, 2019

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1526342400; // May 15, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout =  1567296000; //Sep 1, 2019

        // Deployment of SegWit (BIP141, BIP143, and BIP147)
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 1526342400 ; // May 15, 2018
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout =  1567296000; //Sep 1, 2019

        // The best chain should have at least this much work.
        // consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000006106bead2f4b73");//60988a35d4b6b2
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000001");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x000003d31ae1a51e844d4a83d482b3dd84c545d44c31f3bdeb7c90909fbf3172"); 
        //consensus.defaultAssumeValid = uint256S("0x00"); 

        pchMessageStart[0] = 0x4c;
        pchMessageStart[1] = 0x1a;
        pchMessageStart[2] = 0x2c;
        pchMessageStart[3] = 0xaf;
        nDefaultPort = 17444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1505088000, 293736, 0x1e0ffff0, 1, 100 * COIN);//Time, Nonce,nBits, version, reward
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000405073975ab683f4740808f51a2687a935788473b2621e8357c244649e0"));
        assert(genesis.hashMerkleRoot == uint256S("0x5bab319403ecce5eccd4715162fd72d35313064211ff16fccde441a12b2b93b8"));

        vFixedSeeds.clear();
        vSeeds.clear();
        // nodes with support for servicebits filtering should be at the top
        vSeeds.push_back(CDNSSeedData("5.149.254.11", "5.149.254.11", true));
        //vSeeds.push_back(CDNSSeedData("5.149.254.11", "5.149.254.11"));
        //vSeeds.push_back(CDNSSeedData("", "", true));
        //vSeeds.push_back(CDNSSeedData("", ""));
        //vSeeds.push_back(CDNSSeedData("", ""));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,141);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,211);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;


        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
	
         ( 0, uint256S("0x00000405073975ab683f4740808f51a2687a935788473b2621e8357c244649e0")),
        };

        chainTxData = ChainTxData{
            // Data as of block 00000000c2872f8f8a8935c8e3c5862be9038c97d4de2cf37ed496991166928a (height 1063660)
//            0,
//            0,
//            0
        };

    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP34Height = 100000000; // BIP34 has not activated on regtest (far in the future so block v1 are not rejected in tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in rpc activation tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in rpc activation tests)
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 14 * 24 * 60 * 60; // two weeks
        consensus.nPowTargetSpacing = 10 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = 999999999999ULL;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfc;   
        pchMessageStart[1] = 0xc1;   
        pchMessageStart[2] = 0xb7;   
        pchMessageStart[3] = 0xdc;   
        nDefaultPort = 17445;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1505088000, 293736, 0x1e0ffff0, 1, 100 * COIN);//Time, Nonce,nBits, version, reward
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000405073975ab683f4740808f51a2687a935788473b2621e8357c244649e0"));
        assert(genesis.hashMerkleRoot == uint256S("0x5bab319403ecce5eccd4715162fd72d35313064211ff16fccde441a12b2b93b8"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x00000405073975ab683f4740808f51a2687a935788473b2621e8357c244649e0"))
        };

        chainTxData = ChainTxData{
            0,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,196);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
    }

    void UpdateBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

void UpdateRegtestBIP9Parameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    regTestParams.UpdateBIP9Parameters(d, nStartTime, nTimeout);
}
 

// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2020 The Gold BCR Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <chainparams.h>

#include <chainparamsseeds.h>
#include <consensus/merkle.h>
#include <consensus/consensus.h>
#include <tinyformat.h>
#include <util/system.h>
#include <util/strencodings.h>
#include <versionbitsinfo.h>
#include "arith_uint256.h"

#include <assert.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>


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

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "All India Radio 19-SEP-2020 IPL kicks off in Abhu Dhabi";
    const CScript genesisOutputScript = CScript() << ParseHex("04afab89b3670736e72d7d8a2426081782329142bdfe1c42405c470f54d6e635ee5c6ba66fe3128f7eaf1bcce92b4440a14a6199a40d2f8bb79c452d889b89c3e5") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = CBaseChainParams::MAIN;
        consensus.nSubsidyHalvingInterval = 30000 * 50; // every 8 years 4 months
        consensus.BIP16Exception = uint256S("0x00000545bd5a7bdd90e91f2a7529b4505b96a1d37377ca660b830135fda1ffbf");
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x00000fc5240d2baba8ece9af28a68b0e37149ccb534fab1748179f79dd944114");
        consensus.BIP65Height = 1;
        consensus.BIP66Height = 1;
        consensus.CSVHeight = 1;
        consensus.SegwitHeight = 1;
        consensus.MinBIP9WarningHeight = consensus.SegwitHeight + consensus.nMinerConfirmationWindow;
        consensus.GBCRRewardMatchStep = 40000;
        consensus.GBCRRewardMatchHeight = 3 * consensus.GBCRRewardMatchStep;
        consensus.GBCRDiffAdjHeight = 130000;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("00000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 10 * 3 * 60; // every 10 blocks
        consensus.nPowTargetSpacing = 3 * 60;   // 3 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.fPoSNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.nLastPOWBlock = 500;
        consensus.nMPoSRewardRecipients = 250;  // During the proof of stake phase, maximum of 250 accounts
        consensus.nFirstMPoSBlock = consensus.nLastPOWBlock + 
                                    consensus.nMPoSRewardRecipients + 
                                    COINBASE_MATURITY;
        consensus.nEnableHeaderSignatureHeight = 0;
        consensus.nCheckpointSpan = COINBASE_MATURITY;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000062132e360b8");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0xa7ddda5603f41556ded338d74e2b48045c1548a1518f771e5a979694a4aaf2cf");

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0x67; // g
        pchMessageStart[1] = 0x62; // b
        pchMessageStart[2] = 0x63; // c
        pchMessageStart[3] = 0x72; // r
        nDefaultPort = 62357;
        nPruneAfterHeight = 100000;
        m_assumed_blockchain_size = 2;
        m_assumed_chain_state_size = 1;


       genesis = CreateGenesisBlock(1601828232, 559585, 0x1e0fffff, 1, 50 * COIN);       

       consensus.hashGenesisBlock = genesis.GetHash();
       assert(consensus.hashGenesisBlock == uint256S("0x00000545bd5a7bdd90e91f2a7529b4505b96a1d37377ca660b830135fda1ffbf"));
       assert(genesis.hashMerkleRoot == uint256S("0xa1286c4ccd84131fa2cc016e84709c2e83b5f0785c8876573659e821655a18de"));  

        vFixedSeeds.clear();
        vSeeds.clear();   

       /* Activate Later
       vSeeds.emplace_back("nodea.goldbcr.io");
       vSeeds.emplace_back("nodeb.goldbcr.io");
       vSeeds.emplace_back("nodec.goldbcr.io");
       vSeeds.emplace_back("noded.goldbcr.io");
       vSeeds.emplace_back("nodee.goldbcr.io");
       vSeeds.emplace_back("nodef.goldbcr.io"); 
       */

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,38);  // starts with 'G'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,18);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,148); //  starts with 'L'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x06, 0x90, 0xB4, 0x1F};
        base58Prefixes[EXT_SECRET_KEY] = {0x02, 0x86, 0xAB, 0xE5};

        bech32_hrp = "gbcr";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        m_is_test_chain = false;
        m_is_mockable_chain = false;

        checkpointData = {
            {
                { 0, uint256S("0x00000545bd5a7bdd90e91f2a7529b4505b96a1d37377ca660b830135fda1ffbf")},
                { 333, uint256S("0x00000d4d4aa632e00d199cc0d446778101397e6179badc5f03b5175710d107c1")},
                { 666, uint256S("0x841deb2b688e88ddc6f7a35384638742ab622a940aeb46b03c649fdca7eb6f05")},
                { 999, uint256S("0xfdf3e0f583290401a3f72a07b03f554dc38c34cd1adb9549b0ad6f3920b6b1ec")},
                { 2068, uint256S("0xa7ddda5603f41556ded338d74e2b48045c1548a1518f771e5a979694a4aaf2cf")}
            }
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 128653 b8a8fd8f3a8cbab7f1d2e5d431eab19610ec83d4f6e421f87fa238b1d91e2f92
            /* nTime    */ 1601961920,
            /* nTxCount */ 3647,
            /* dTxRate  */ 0.08542301382704476,
        };
    }
};

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = CBaseChainParams::TESTNET;
        consensus.nSubsidyHalvingInterval = 30000;
        consensus.BIP16Exception = uint256S("0x00");
        consensus.BIP34Height = 1;
        consensus.BIP34Hash = uint256S("0x00000fe2acf48e35c5b594d9ff7db2a7bbafa1b73205b2789a6833be70595818");
        consensus.BIP65Height = 1;
        consensus.BIP66Height = 1;
        consensus.CSVHeight = 1;
        consensus.SegwitHeight = 1;
        consensus.MinBIP9WarningHeight = consensus.SegwitHeight + consensus.nMinerConfirmationWindow;
        consensus.GBCRRewardMatchStep = 400;
        consensus.GBCRRewardMatchHeight = 3 * consensus.GBCRRewardMatchStep;
        consensus.GBCRDiffAdjHeight = 1500;
        consensus.powLimit = uint256S("00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("0000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 10 * 1 * 60; // every 10 blocks
        consensus.nPowTargetSpacing = 1 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.fPoSNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.nLastPOWBlock = 501;
        consensus.nMPoSRewardRecipients = 1;
        consensus.nFirstMPoSBlock = consensus.nLastPOWBlock + 
                                    consensus.nMPoSRewardRecipients + 
                                    COINBASE_MATURITY;
        consensus.nEnableHeaderSignatureHeight = 0;
        consensus.nCheckpointSpan = COINBASE_MATURITY;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x0000056be7048ae43e3c75d7261acfc6b3753c92d63e23d389f4c2823eb52921"); // 0

        pchMessageStart[0] = 0x47; // G
        pchMessageStart[1] = 0x42; // B
        pchMessageStart[2] = 0x43; // C
        pchMessageStart[3] = 0x52; // R
        nDefaultPort = 72357;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 40;
        m_assumed_chain_state_size = 2;

        genesis = CreateGenesisBlock(1601168612, 2615756, 0x1e0fffff, 1, 50 * COIN);       
        
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000056be7048ae43e3c75d7261acfc6b3753c92d63e23d389f4c2823eb52921"));
        assert(genesis.hashMerkleRoot == uint256S("0xa1286c4ccd84131fa2cc016e84709c2e83b5f0785c8876573659e821655a18de"));

        vFixedSeeds.clear();
        vSeeds.clear();       

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,78);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,130);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tgbcr";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        m_is_test_chain = true;
        m_is_mockable_chain = false;

        checkpointData = {
            {
                {0, uint256S("0x0000056be7048ae43e3c75d7261acfc6b3753c92d63e23d389f4c2823eb52921")},
            }
        };

        chainTxData = ChainTxData{
            // Data from RPC: getchaintxstats 4096 00000000000000b7ab6ce61eb6d571003fbe5fe892da4c9b740c49a07542462d
            /* nTime    */ 1601168612,
            /* nTxCount */ 0,
            /* dTxRate  */ 0.0,
        };
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    explicit CRegTestParams(const ArgsManager& args) {
        strNetworkID =  CBaseChainParams::REGTEST;
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Exception = uint256();
        consensus.BIP34Height = 500; // BIP34 activated on regtest (Used in functional tests)
        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351; // BIP65 activated on regtest (Used in functional tests)
        consensus.BIP66Height = 1251; // BIP66 activated on regtest (Used in functional tests)
        consensus.CSVHeight = 432; // CSV activated on regtest (Used in rpc activation tests)
        consensus.SegwitHeight = 0; // SEGWIT is always activated on regtest unless overridden
        consensus.MinBIP9WarningHeight = 0;
        consensus.GBCRRewardMatchStep = 400;
        consensus.GBCRRewardMatchHeight = 3 * consensus.GBCRRewardMatchStep;
        consensus.GBCRDiffAdjHeight = 1500;
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 10 * 3 * 60; // every 10 blocks
        consensus.nPowTargetSpacing = 3 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.fPoSNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.nLastPOWBlock = 0x7fffffff;
        consensus.nMPoSRewardRecipients = 10;
        consensus.nFirstMPoSBlock = 5000;
        consensus.nEnableHeaderSignatureHeight = 0;
        consensus.nCheckpointSpan = COINBASE_MATURITY;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        // The best chain should have at least this much work.
        consensus.nMinimumChainWork = uint256S("0x00");

        // By default assume that the signatures in ancestors of this block are valid.
        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xbf;
        pchMessageStart[2] = 0xb5;
        pchMessageStart[3] = 0xda;
        nDefaultPort = 48934;
        nPruneAfterHeight = 1000;
        m_assumed_blockchain_size = 0;
        m_assumed_chain_state_size = 0;

        UpdateActivationParametersFromArgs(args);

        genesis = CreateGenesisBlock(1601168612, 2615756, 0x1e0fffff, 1, 50 * COIN);

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000056be7048ae43e3c75d7261acfc6b3753c92d63e23d389f4c2823eb52921"));
        assert(genesis.hashMerkleRoot == uint256S("0xa1286c4ccd84131fa2cc016e84709c2e83b5f0785c8876573659e821655a18de"));

        vFixedSeeds.clear(); //!< Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();      //!< Regtest mode doesn't have any DNS seeds.

        fDefaultConsistencyChecks = true;
        fRequireStandard = true;
        m_is_test_chain = true;
        m_is_mockable_chain = true;

        checkpointData = {
            {
                {0, uint256S("0x0000056be7048ae43e3c75d7261acfc6b3753c92d63e23d389f4c2823eb52921")},
            }
        };

        chainTxData = ChainTxData{
            1601168612,
            0,
            0
        };

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,65);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,78);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,130);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "rgbcr";
    }

    /**
     * Allows modifying the Version Bits regtest parameters.
     */
    void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
    {
        consensus.vDeployments[d].nStartTime = nStartTime;
        consensus.vDeployments[d].nTimeout = nTimeout;
    }
    void UpdateActivationParametersFromArgs(const ArgsManager& args);
};

void CRegTestParams::UpdateActivationParametersFromArgs(const ArgsManager& args)
{
    if (gArgs.IsArgSet("-segwitheight")) {  
        int64_t height = gArgs.GetArg("-segwitheight", consensus.SegwitHeight);;
        if (height < -1 || height >= std::numeric_limits<int>::max()) {
            throw std::runtime_error(strprintf("Activation height %ld for segwit is out of valid range. Use -1 to disable segwit.", height));
        } else if (height == -1) {
            LogPrintf("Segwit disabled for testing\n");
            height = std::numeric_limits<int>::max();
        }
        consensus.SegwitHeight = static_cast<int>(height);
    }

    if (!args.IsArgSet("-vbparams")) return;

    for (const std::string& strDeployment : args.GetArgs("-vbparams")) {
        std::vector<std::string> vDeploymentParams;
        boost::split(vDeploymentParams, strDeployment, boost::is_any_of(":"));
        if (vDeploymentParams.size() != 3) {
            throw std::runtime_error("Version bits parameters malformed, expecting deployment:start:end");
        }
        int64_t nStartTime, nTimeout;
        if (!ParseInt64(vDeploymentParams[1], &nStartTime)) {
            throw std::runtime_error(strprintf("Invalid nStartTime (%s)", vDeploymentParams[1]));
        }
        if (!ParseInt64(vDeploymentParams[2], &nTimeout)) {
            throw std::runtime_error(strprintf("Invalid nTimeout (%s)", vDeploymentParams[2]));
        }
        bool found = false;
        for (int j=0; j < (int)Consensus::MAX_VERSION_BITS_DEPLOYMENTS; ++j) {
            if (vDeploymentParams[0] == VersionBitsDeploymentInfo[j].name) {
                UpdateVersionBitsParameters(Consensus::DeploymentPos(j), nStartTime, nTimeout);
                found = true;
                LogPrintf("Setting version bits activation parameters for %s to start=%ld, timeout=%ld\n", vDeploymentParams[0], nStartTime, nTimeout);
                break;
            }
        }
        if (!found) {
            throw std::runtime_error(strprintf("Invalid deployment (%s)", vDeploymentParams[0]));
        }
    }
}

static std::unique_ptr<const CChainParams> globalChainParams;

const CChainParams &Params() {
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<const CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams(gArgs));
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}


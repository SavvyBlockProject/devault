// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CONSENSUS_PARAMS_H
#define BITCOIN_CONSENSUS_PARAMS_H

#include "amount.h"
#include "uint256.h"

#include <map>
#include <set>
#include <string>

namespace Consensus {

enum DeploymentPos {
    DEPLOYMENT_TESTDUMMY,
    // NOTE: Also add new deployments to VersionBitsDeploymentInfo in
    // versionbits.cpp
    MAX_VERSION_BITS_DEPLOYMENTS
};

/**
 * Struct for each individual consensus rule change using BIP9.
 */
struct BIP9Deployment {
    /** Bit position to select the particular bit in nVersion. */
    int bit;
    /**
     * Start MedianTime for version bits miner confirmation. Can be a date in
     * the past.
     */
    int64_t nStartTime;
    /** Timeout/expiry MedianTime for the deployment attempt. */
    int64_t nTimeout;
};

/**
 * Parameters that influence chain consensus.
 */
struct Params {
    uint256 hashGenesisBlock;
    /** Block height at which UAHF kicks in */
    int uahfHeight;
    /** Unix time used for MTP activation of 15 May 2019 12:00:00 UTC upgrade */
    int greatWallActivationTime;
    /**
     * Minimum blocks including miner confirmation of the total of 2016 blocks
     * in a retargeting period, (nPowTargetTimespan / nPowTargetSpacing) which
     * is also used for BIP9 deployments.
     * Examples: 1916 for 95%, 1512 for testchains.
     */
    uint32_t nRuleChangeActivationThreshold;
    uint32_t nMinerConfirmationWindow;
    BIP9Deployment vDeployments[MAX_VERSION_BITS_DEPLOYMENTS];
    /** Proof of work parameters */
    uint256 powLimit;
    bool fPowAllowMinDifficultyBlocks;
    bool fPowNoRetargeting;
    int64_t nPowTargetSpacing;
    int64_t nPowTargetTimespan;
    int64_t nBlocksPerYear;
    int64_t nInitialMiningRewardInCoins;
    int64_t minerCapSystemChangeHeight;

    // Rewards
    std::vector<int64_t> nPerCentPerYear;
    int64_t nMinRewardBlocks;
    Amount nMinRewardBalance;
    Amount nMinReward;
    Amount nMaxReward;
  
    std::set<std::string> minerWhiteListAdminAddress;
    int64_t DifficultyAdjustmentInterval() const {
        return nPowTargetTimespan / nPowTargetSpacing;
    }
    uint256 nMinimumChainWork;
    uint256 defaultAssumeValid;

    // Params for Zawy's LWMA difficulty adjustment algorithm.
    int64_t nZawyLwmaAveragingWindow;
    int64_t nZawyLwmaAdjustedWeight;  // k = (N+1)/2 * 0.998 * T
    int64_t nZawyLwmaMinDenominator;
    bool bZawyLwmaSolvetimeLimitation;

};
} // namespace Consensus

#endif // DEVAULT_CONSENSUS_PARAMS_H

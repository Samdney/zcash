/**
 * @file       Address.h
 *
 * @brief      Address and PublicAddress classes for the Zerocash library.
 *
 * @author     Christina Garman, Matthew Green, and Ian Miers
 * @date       April 2014
 *
 * @copyright  Copyright 2014 Christina Garman, Matthew Green, and Ian Miers
 * @license    This project is released under the MIT license.
 **/

#ifndef ADDRESS_H_
#define ADDRESS_H_

#include <vector>
#include <string>

#include "../serialize.h"

namespace libzerocash {

class PublicAddress {

friend class Address;
friend class Coin;
friend class PourTransaction;

public:
	PublicAddress();
    PublicAddress(const std::vector<unsigned char>& a_sk, const std::string sk_enc);

	bool operator==(const PublicAddress& rhs) const;
	bool operator!=(const PublicAddress& rhs) const;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(a_pk);
        READWRITE(pk_enc);
    }

private:
	std::vector<unsigned char> a_pk;
	std::string pk_enc;

    void createPublicAddress(const std::vector<unsigned char>& a_sk, const std::string sk_enc);

    const std::vector<unsigned char>& getPublicAddressSecret() const;

	const std::string getEncryptionPublicKey() const;
};

class Address {

friend class PourTransaction;

public:
	/** Create a new address to recieve coins from
	 *
	 */
	Address();

	const PublicAddress& getPublicAddress() const;

	bool operator==(const Address& rhs) const;
	bool operator!=(const Address& rhs) const;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
        READWRITE(addr_pk);
        READWRITE(a_sk);
        READWRITE(sk_enc);
    }

private:
	PublicAddress addr_pk;
	std::vector<unsigned char> a_sk;
    std::string sk_enc;

    const std::vector<unsigned char>& getAddressSecret() const;

	const std::string getEncryptionSecretKey() const;
};

} /* namespace libzerocash */
#endif /* ADDRESS_H_ */
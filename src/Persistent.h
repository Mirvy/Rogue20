#ifndef PERSISTENT_H
#define PERSISTENT_H
#include "boost/serialization/serialization.hpp"
#include "boost/archive/text_iarchive.hpp"
#include "boost/archive/text_oarchive.hpp"
#include "boost/serialization/base_object.hpp"
#include "boost/serialization/split_member.hpp"
#include "boost/serialization/access.hpp"

/***************************************//*!**********
 * \brief INTERFACE - Save/Load
 *
 *
 * This interface allows for game elements to be saved
 * using TCODZip.
 ****************************************************/

class Persistent {
	public :
        virtual ~Persistent() {}
        virtual void save(boost::archive::text_oarchive &ar, const unsigned int version) = 0;
        virtual void load(boost::archive::text_iarchive &ar, const unsigned int version) = 0;
        static const TCODColor *assignTCODColor(int r, int g, int b);
        friend class boost::serialization::access;
        BOOST_SERIALIZATION_SPLIT_MEMBER()
};


#endif

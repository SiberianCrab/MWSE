#include "TES3Attachment.h"

#include "TES3Misc.h"

namespace TES3 {

	//
	// LockAttachment
	//

	Misc* LockAttachmentNode::getKey() const {
		return key;
	}

	void LockAttachmentNode::setKey(Misc* k) {
		if (k && !k->getIsKey()) {
			throw std::invalid_argument("Invalid key specified. Object is not a key.");
		}

		key = k;
	}
}

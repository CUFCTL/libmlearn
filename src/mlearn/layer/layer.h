/**
 * @file layer/layer.h
 *
 * Interface definitions for the abstract layer type.
 */
#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include "mlearn/math/matrix.h"
#include "mlearn/util/iodevice.h"



namespace ML {



class Layer {
public:
	virtual ~Layer() {};

	virtual void save(IODevice& file) const = 0;
	virtual void load(IODevice& file) = 0;
	virtual void print() const = 0;
};



IODevice& operator<<(IODevice& file, const Layer* layer);
IODevice& operator>>(IODevice& file, Layer* layer);



}

#endif

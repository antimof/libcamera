/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * Copyright (C) 2019, Google Inc.
 *
 * ipa_interface.cpp - Image Processing Algorithm interface
 */

#include <libcamera/ipa/ipa_interface.h>

/**
 * \file ipa_interface.h
 * \brief Image Processing Algorithm interface
 *
 * Every pipeline handler in libcamera may attach some or all of its cameras to
 * an Image Processing Algorithm (IPA) module. An IPA module is developed for a
 * specific pipeline handler and each pipeline handler may be compatible with
 * multiple IPA implementations, both open and closed source. To support this,
 * libcamera communicates with IPA modules through a per-pipeline C++ interface.
 *
 * IPA modules shall provide an ipaCreate() function exported as a public C
 * symbol with the following prototype:
 *
 * \code{.c}
 * IPAInterface *ipaCreate();
 * \endcode
 *
 * The ipaCreate() function creates an instance of an IPA interface, which models
 * a context of execution for the IPA. IPA modules shall support creating one
 * context per camera, as required by their associated pipeline handler.
 *
 * The IPA module interface operations are defined in the mojom file
 * corresponding to the pipeline handler, in
 * include/libcamera/ipa/{pipeline_name}.mojom.
 *
 * The IPA interface is specific to each pipeline handler. The pipeline handlers
 * define a set of operations used to communicate with their IPA modules. The
 * operations, along with the data structures they use, are collectively
 * referred to as the IPA protocol.
 *
 * The IPA protocol is defined using the
 * <a href="https://chromium.googlesource.com/chromium/src/+/master/mojo/public/tools/bindings/README.md">Mojo interface definition language</a>,
 * in a Mojo module file stored in include/libcamera/ipa/{pipeline_name}.mojom.
 * The Mojo module contains two Mojo interfaces: IPAInterface defines the
 * operations exposed by the IPA and called by the pipeline handler, and
 * IPAEventInterface defines the events generated by the IPA and received by the
 * pipeline handler.
 *
 * \todo Add reference to how pipelines shall document their protocol.
 *
 * IPAs can be isolated in a separate process. This implies that arguments to
 * the IPA interface functions may need to be transferred over IPC. An IPA
 * proxy is auto-generated based on the mojom file, which abstracts away the
 * (de)serialization from the pipeline handler and the IPA implementation. Thus
 * any C++ structure that is defined in the mojom file, or the C++ libcamera
 * objects that are listed in core.mojom, can be used directly.
 *
 * Due to IPC, synchronous communication between pipeline handlers and IPAs can
 * be costly. For that reason, functions that cannot afford the high cost
 * should be marked as [async] in the mojom file, and they will operate
 * asynchronously. This implies that these functions don't return a status, and
 * that all functions may copy their arguments. Synchronous functions are still
 * allowed, but should be used with caution.
 */

/**
 * \fn ipaCreate()
 * \brief Entry point to the IPA modules
 *
 * This function is the entry point to the IPA modules. It is implemented by
 * every IPA module, and called by libcamera to create a new IPA interface
 * instance.
 *
 * \return A newly created IPA interface instance
 */

namespace libcamera {

/**
 * \class IPAInterface
 * \brief C++ Interface for IPA implementation
 *
 * This pure virtual class defines a skeletal C++ API for IPA modules.
 * Specializations of this class must be defined in a mojom file in
 * include/libcamera/ipa/ (see the IPA Writers Guide for details
 * on how to do so).
 *
 * Due to process isolation all arguments to the IPAInterface member functions
 * and signals may need to be transferred over IPC. The class thus uses
 * serializable data types only. The IPA C++ interface defines custom data
 * structures that mirror core libcamera structures when the latter are not
 * suitable, such as IPAStream to carry StreamConfiguration data.
 *
 * Custom data structures may also be defined in the mojom file, in which case
 * the (de)serialization will automatically be generated. If any other libcamera
 * structures are to be used as parameters, then a (de)serializer for them must
 * be implemented in IPADataSerializer.
 *
 * The pipeline handlers shall use the IPAManager to locate a compatible
 * IPAInterface. The interface may then be used to interact with the IPA module.
 *
 * \todo Figure out how to generate IPAInterface documentation.
 */

} /* namespace libcamera */

// @HEADER
// *****************************************************************************
//                     Pamgen Package
//
// Copyright 2004 NTESS and the Pamgen contributors.
// SPDX-License-Identifier: LGPL-2.1-or-later
// *****************************************************************************
// @HEADER

#ifndef _NORMALBLOCKRTC_H
#define _NORMALBLOCKRTC_H

#include "RTC_BlockRTC.hh"
#include "RTC_TokenizerRTC.hh"

#include <string>
#include <map>

namespace PG_RuntimeCompiler {

/**
 * A NormalBlock represents a block of code that executes unconditionally.
 * NormalBlock extends Block because it is a Block.
 */

class NormalBlock : public Block
{
 public:

  /**
   * Constructor -> The constructor creates the parent Block and tells the
   *                parent to create its sub statements
   *
   * @param vars  - A map of already active variables
   * @param lines - The array of strings that represent the lines of the code.
   * @param errs  - A string containing the errors that have been generated by
   *                the compiling of lines. If errs is not empty, then the
   *                program has not compiled succesfully
   */
  NormalBlock(std::map<std::string, Variable*> vars, Tokenizer& lines,
	      std::string& errs);

  /**
   * Destructor -> The destructor is a no-op.
   */
  ~NormalBlock() {}

  /**
   * execute -> This method executes this NormalBlock.
   */
  Value* execute();
};

}

#endif


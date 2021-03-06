// Copyright(C) 1999-2010
// Sandia Corporation. Under the terms of Contract
// DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
// certain rights in this software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of Sandia Corporation nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <Ioss_DatabaseIO.h>
#include <Ioss_ElementTopology.h>
#include <Ioss_Property.h>
#include <Ioss_Region.h>
#include <Ioss_SideBlock.h>
#include <Ioss_SideSet.h>
#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

#include "Ioss_GroupingEntity.h"
#include "Ioss_PropertyManager.h"

namespace Ioss {
  class Field;
} // namespace Ioss

static const std::string SCALAR("scalar");

/** \brief Create a side set with no members initially.
 *
 *  \param[in] io_database The database associated with the region containing the side set.
 *  \param[in] my_name The side set's name.
 */
Ioss::SideSet::SideSet(Ioss::DatabaseIO *io_database, const std::string &my_name)
    : Ioss::GroupingEntity(io_database, my_name, 0)
{
  properties.add(Ioss::Property(this, "side_block_count", Ioss::Property::INTEGER));
  properties.add(Ioss::Property(this, "block_count", Ioss::Property::INTEGER));
}

Ioss::SideSet::~SideSet()
{
  try {
    for (auto sb : sideBlocks) {
      delete sb;
    }
  }
  catch (...) {
  }
}

const Ioss::SideBlockContainer &Ioss::SideSet::get_side_blocks() const { return sideBlocks; }

Ioss::SideBlock *Ioss::SideSet::get_block(size_t which) const
{
  IOSS_FUNC_ENTER(m_);
  if (which < sideBlocks.size()) {
    return sideBlocks[which];
  }

  return nullptr;
}

Ioss::SideBlock *Ioss::SideSet::get_side_block(const std::string &my_name) const
{
  IOSS_FUNC_ENTER(m_);
  Ioss::SideBlock *ge = nullptr;
  for (auto sb : sideBlocks) {
    if (sb->name() == my_name) {
      ge = sb;
      break;
    }
  }
  return ge;
}

bool Ioss::SideSet::add(Ioss::SideBlock *side_block)
{
  IOSS_FUNC_ENTER(m_);
  sideBlocks.push_back(side_block);
  side_block->owner_ = this;
  return true;
}

int64_t Ioss::SideSet::internal_get_field_data(const Ioss::Field &field, void *data,
                                               size_t data_size) const
{
  return get_database()->get_field(this, field, data, data_size);
}

int64_t Ioss::SideSet::internal_put_field_data(const Ioss::Field &field, void *data,
                                               size_t data_size) const
{
  return get_database()->put_field(this, field, data, data_size);
}

Ioss::Property Ioss::SideSet::get_implicit_property(const std::string &my_name) const
{
  if (my_name == "side_block_count") {
    return Ioss::Property(my_name, static_cast<int>(sideBlocks.size()));
  }
  if (my_name == "block_count") {
    return Ioss::Property(my_name, static_cast<int>(sideBlocks.size()));
  }

  return Ioss::GroupingEntity::get_implicit_property(my_name);
}

int Ioss::SideSet::max_parametric_dimension() const
{
  IOSS_FUNC_ENTER(m_);
  int max_par_dim = 0;
  for (auto sideblock : sideBlocks) {
    int parametric_dim = sideblock->topology()->parametric_dimension();
    if (parametric_dim > max_par_dim) {
      max_par_dim = parametric_dim;
    }
  }
  if (max_par_dim == 0) {
    // If the sideset is empty, return the maximum that the parametric dimension
    // could be...
    // Faces for 3D model; Edges for 2D model
    const Ioss::Region *reg = get_database()->get_region();
    max_par_dim             = reg->get_property("spatial_dimension").get_int() - 1;
  }
  return max_par_dim;
}

void Ioss::SideSet::block_membership(std::vector<std::string> &block_members)
{
  IOSS_FUNC_ENTER(m_);
  if (blockMembership.empty()) {
    for (auto &sb : sideBlocks) {
      std::vector<std::string> blocks;
      sb->block_membership(blocks);
      blockMembership.insert(blockMembership.end(), blocks.begin(), blocks.end());
    }
    Ioss::Utils::uniquify(blockMembership);
  }
  block_members = blockMembership;
}

/*
 * Software License Agreement (BSD License)
 *
 *  Point Cloud Library (PCL) - www.pointclouds.org
 *  Copyright (c) 2012-, Open Perception, Inc.
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the copyright holder(s) nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once

#include <pcl/pcl_macros.h>
#include <pcl/io/file_io.h>
#include <pcl/PCLPointField.h>
#include <pcl/common/io.h>
#include <pcl/common/utils.h> // pcl::utils::ignore


namespace pcl
{
  /** \brief Ascii Point Cloud Reader.
    * Read any ASCII file by setting the separating characters and input point fields.
    *
    * \author Adam Stambler (adasta@gmail.com)
    * \ingroup io
    */
  class PCL_EXPORTS ASCIIReader : public FileReader
  {
    public:
      ASCIIReader ();
      ~ASCIIReader () override;
      using FileReader::read;

      /* Load only the meta information (number of points, their types, etc),
        * and not the points themselves, from a given FILE file. Useful for fast
        * evaluation of the underlying data structure.
        *
        * Returns:
        *  * < 0 (-1) on error
        *  * > 0 on success
        * \param[in] file_name the name of the file to load
        * \param[out] cloud the resultant point cloud dataset (only the header will be filled)
        * \param[out] origin the sensor acquisition origin (only for > FILE_V7 - null if not present)
        * \param[out] orientation the sensor acquisition orientation (only for > FILE_V7 - identity if not present)
        * \param[out] file_version the FILE version of the file (either FILE_V6 or FILE_V7)
        * \param[out] data_type the type of data (binary data=1, ascii=0, etc)
        * \param[out] data_idx the offset of cloud data within the file
        * \param[in] offset the offset in the file where to expect the true header to begin.
        * One usage example for setting the offset parameter is for reading
        * data from a TAR "archive containing multiple files: TAR files always
        * add a 512 byte header in front of the actual file, so set the offset
        * to the next byte after the header (e.g., 513).
        */
      int
      readHeader (const std::string &file_name, pcl::PCLPointCloud2 &cloud,
                  Eigen::Vector4f &origin, Eigen::Quaternionf &orientation,
                  int &file_version, int &data_type, unsigned int &data_idx, const int offset = 0) override ;


      /** \brief Read a point cloud data from a FILE file and store it into a pcl/PCLPointCloud2.
        * \param[in] file_name the name of the file containing the actual PointCloud data
        * \param[out] cloud the resultant PointCloud message read from disk
        * \param[out] origin the sensor acquisition origin (only for > FILE_V7 - null if not present)
        * \param[out] orientation the sensor acquisition orientation (only for > FILE_V7 - identity if not present)
        * \param[out] file_version the FILE version of the file (either FILE_V6 or FILE_V7)
        * \param[in] offset the offset in the file where to expect the true header to begin.
        * One usage example for setting the offset parameter is for reading
        * data from a TAR "archive containing multiple files: TAR files always
        * add a 512 byte header in front of the actual file, so set the offset
        * to the next byte after the header (e.g., 513).
        */
      int
      read (const std::string &file_name, pcl::PCLPointCloud2 &cloud,
            Eigen::Vector4f &origin, Eigen::Quaternionf &orientation, int &file_version,
            const int offset = 0) override;

      /** \brief Set the ascii file point fields.
        */
      template<typename PointT>
      void setInputFields ();

      /** \brief Set the ascii file point fields using a list of fields.
        * \param[in] fields  is a list of point fields, in order, in the input ascii file
        */
      void 
      setInputFields (const std::vector<pcl::PCLPointField>& fields);

      /** \brief Set the Separating characters for the ascii point fields 2.
        * \param[in] chars string of separating characters
        *  Sets the separating characters for the point fields.  The
        *  default separating characters are " \n\t,"
        */
      void 
      setSepChars (const std::string &chars);

      /** \brief Set the extension of the ascii point file type.
        * \param[in] ext   extension (example :  ".txt" or ".xyz" )
        */
      void 
      setExtension (const std::string &ext) { extension_ = ext; }

    protected:
      std::string sep_chars_;
      std::string extension_;
      std::vector<pcl::PCLPointField> fields_;
      std::string name_;


      /** \brief Parses token based on field type.
        * \param[in] token   string representation of point fields
        * \param[in] field   token point field type
        * \param[out] data_target  address that the point field data should be assigned to
        *  returns the size of the parsed point field in bytes
        */
      int 
      parse (const std::string& token, const pcl::PCLPointField& field, std::uint8_t* data_target);

      /** \brief Returns the size in bytes of a point field type.
        * \param[in] type   point field type
        *  returns the size of the type in bytes
        */
      std::uint32_t 
      typeSize (int type);
	};
}

#include <pcl/io/impl/ascii_io.hpp>

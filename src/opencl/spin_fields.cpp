#include <sstream>

#include "atoms.hpp"

#include "data.hpp"
#include "exchange_fields.hpp"
#include "internal.hpp"
#include "opencl_include.hpp"
#include "opencl_utils.hpp"
#include "typedefs.hpp"

#ifdef OPENCL

namespace vcl = ::vopencl::internal;

namespace vopencl
{
   namespace internal
   {
      bool compiled_update_spin_fields = false;
      cl::Kernel update_nexch_spin_fields;

      void update_spin_fields(void) noexcept
      {
         size_t buffer_size = ::atoms::num_atoms * sizeof(vcl_real_t);

         // Zero the field buffers
         vcl_real_t zero = 0.0;
         vcl::queue.enqueueFillBuffer(vcl::total_spin_field_array.x(),
                                   &zero,
                                   sizeof(vcl_real_t),
                                   buffer_size);
         vcl::queue.enqueueFillBuffer(vcl::total_spin_field_array.y(),
                                   &zero,
                                   sizeof(vcl_real_t),
                                   buffer_size);
         vcl::queue.enqueueFillBuffer(vcl::total_spin_field_array.z(),
                                   &zero,
                                   sizeof(vcl_real_t),
                                   buffer_size);

         if (!compiled_update_spin_fields)
         {
            std::ostringstream opts;
            opts << "-DNUM_ATOMS=" << ::atoms::num_atoms;
            update_nexch_spin_fields = vcl::build_kernel_from_file("src/opencl/cl/spin_fields.cl",
                                                                   "update_nexch_spin_fields",
                                                                   vcl::context, vcl::default_device,
                                                                   opts.str());
            compiled_update_spin_fields = true;

            vcl::set_kernel_args(update_nexch_spin_fields,
                                 vcl::atoms::type_array,
                                 vcl::mp::materials,
                                 vcl::atoms::spin_array.x(),
                                 vcl::atoms::spin_array.y(),
                                 vcl::atoms::spin_array.z(),
                                 vcl::total_spin_field_array.x(),
                                 vcl::total_spin_field_array.y(),
                                 vcl::total_spin_field_array.z());
         }

         cl::NDRange global(::atoms::num_atoms);

         vcl::kernel_call(update_nexch_spin_fields, vcl::queue, global, vcl::local);


         vcl::exchange::calculate_exchange_fields();
      }
   }
}

#endif // OPENCL

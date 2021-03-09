#include <_cpu_.h>

#if defined (LINUX)
#  include <stdio.h>
#elif defined (DARWIN)
#  include <sys/sysctl.h>
#elif defined (WINNT)
#  include <windows.h>
#  include <intrin.h>
#  pragma warning(disable : 4996)
#endif


#include <stdint.h>
#include <string.h>
#include <stdio.h>

typedef struct cpu_s {
	char machine[64];
	int byte_order;
	int ncpu;
	size_t cache_line_size;
  char vendor_id[64];
} cpu_s;

cpu_s *get_arch(cpu_s *cpu);
cpu_s *get_byte_order(cpu_s *cpu);
cpu_s *get_cache_line_size(cpu_s *cpu);
cpu_s *get_vendor_id(cpu_s *cpu);

cpu_s*
get_arch(cpu_s *cpu)
{
  _unused_(cpu);
  return 0;
}

cpu_s*
get_byte_order(cpu_s *cpu)
{
  _unused_(cpu);
  return 0;
}

cpu_s*
get_cache_line_size(cpu_s *cpu) {

#if defined (LINUX)
	FILE *f = fopen("/sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size", "r");
	if (f) {
		if (!fscanf(f, "%zu", &cpu->cache_line_size)) {
      cpu->cache_line_size = 0;
    }
		fclose(f);
	}
	
#elif defined (DARWIN)
	size_t size = 0;

	sysctlbyname("hw.machine", 0, &size, 0, 0);
	sysctlbyname("hw.machine", cpu->machine, &size, 0, 0);

	size = sizeof(cpu->byte_order);
	sysctlbyname("hw.byteorder", &cpu->byte_order, &size, 0, 0);

	size = sizeof(cpu->cache_line_size);
	sysctlbyname("hw.cachelinesize", &cpu->cache_line_size, &size, 0, 0);

#elif defined (WINNT)
	DWORD buffer_size = 0;
	SYSTEM_LOGICAL_PROCESSOR_INFORMATION *buffer = 0;

	GetLogicalProcessorInformation(0, &buffer_size);
	buffer = malloc(buffer_size);
	GetLogicalProcessorInformation(&buffer[0], &buffer_size);

	for (DWORD i = 0; i != buffer_size / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION); ++i) {
		if (buffer[i].Relationship == RelationCache && buffer[i].Cache.Level == 1) {
			cpu->cache_line_size = buffer[i].Cache.LineSize;
			break;
		}
	}
	free(buffer);

#endif

	return cpu;
}

cpu_s*
get_vendor_id(cpu_s *cpu)
{
  uint32_t fn = 0;
  uint32_t buf[5];
  memset(buf, 0, sizeof(buf));
  
#if ( MSVC )

  __cpuid((int32_t*) buf, fn);

#elif ( __amd64__ ) || ( __x86_64__ )

  uint32_t eax, ebx, ecx, edx;
  __asm__ (
           "cpuid"
           : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
           : "a" (fn)
  );

  buf[0] = eax;
  buf[1] = ebx;
  buf[2] = ecx;
  buf[3] = edx;

#else
	
  _unused_(fn);
  _unused_(buf);
  return NULL;
	
#endif

  const size_t w = sizeof(uint32_t);
  char *p = (char*)&cpu->vendor_id[0];

  /* ebx, edx, ecx */
  memcpy(p, (const char *) &buf[1], w);
  memcpy(p += w, (const char *) &buf[3], w);
  memcpy(p += w, (const char *) &buf[2], w);

  return cpu;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	cpu_s cpu;
	memset(&cpu, 0, sizeof(cpu));

  get_arch(&cpu);
  get_byte_order(&cpu);
	get_cache_line_size(&cpu);
  get_vendor_id(&cpu);

	printf("Architecture: %s\n", cpu.machine);
	printf("Byte Order: %s\n", 
				 (1234 == cpu.byte_order ? "Little Endian" : "Big Endian"));
	printf("Cache Line Size: %zu\n", cpu.cache_line_size);
	printf("Vendor Id: %s\n", cpu.vendor_id);
}


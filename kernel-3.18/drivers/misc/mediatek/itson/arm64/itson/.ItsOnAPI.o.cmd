cmd_/home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/ItsOnAPI.o := /home/administrator/Build/linux_repo/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/aarch64-linux-android-gcc -Wp,-MD,/home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/.ItsOnAPI.o.d  -nostdinc -isystem /home/administrator/Build/linux_repo/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/bin/../lib/gcc/aarch64-linux-android/4.9.x-google/include -I/home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include -Iarch/arm64/include/generated  -I/home/administrator/Build/linux_repo/kernel-3.18/include -Iinclude -I/home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi -Iarch/arm64/include/generated/uapi -I/home/administrator/Build/linux_repo/kernel-3.18/include/uapi -Iinclude/generated/uapi -include /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kconfig.h   -I/home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson -D__KERNEL__ -mlittle-endian -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -std=gnu89 -mgeneral-regs-only -fno-pic -fno-delete-null-pointer-checks -O2 --param=allow-store-data-races=0 -Werror=frame-larger-than=1 -Wframe-larger-than=1400 -fno-stack-protector -Wno-unused-but-set-variable -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-var-tracking-assignments -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack -Werror=implicit-int -Werror=strict-prototypes -Werror=date-time -DPURGE_LOG -DKERNELVERSION=3 -DITSON_SECURE_LEVEL1_UID="{ 1013, 1000 }" -DITSON_SECURE_LEVEL2_UID="{ 1500 }"  -DMODULE -fno-pic -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(ItsOnAPI)"  -D"KBUILD_MODNAME=KBUILD_STR(module1)" -c -o /home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/ItsOnAPI.o /home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/ItsOnAPI.c

source_/home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/ItsOnAPI.o := /home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/ItsOnAPI.c

deps_/home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/ItsOnAPI.o := \
    $(wildcard include/config/bridge/netfilter.h) \
    $(wildcard include/config/uidgid/strict/type/checks.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/module.h \
    $(wildcard include/config/sysfs.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/unused/symbols.h) \
    $(wildcard include/config/module/sig.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/kallsyms.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/tracepoints.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/module/unload.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/debug/set/module/ronx.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/list.h \
    $(wildcard include/config/debug/list.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/types.h \
    $(wildcard include/config/uid16.h) \
    $(wildcard include/config/lbdaf.h) \
    $(wildcard include/config/arch/dma/addr/t/64bit.h) \
    $(wildcard include/config/phys/addr/t/64bit.h) \
    $(wildcard include/config/64bit.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/types.h \
  arch/arm64/include/generated/asm/types.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/types.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/int-ll64.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/int-ll64.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/bitsperlong.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitsperlong.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/bitsperlong.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/posix_types.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/stddef.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/stddef.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/compiler-gcc.h \
    $(wildcard include/config/arch/supports/optimized/inlining.h) \
    $(wildcard include/config/optimize/inlining.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/compiler-gcc4.h \
    $(wildcard include/config/arch/use/builtin/bswap.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/posix_types.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/posix_types.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/poison.h \
    $(wildcard include/config/illegal/pointer/value.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/const.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kernel.h \
    $(wildcard include/config/preempt/voluntary.h) \
    $(wildcard include/config/debug/atomic/sleep.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/prove/locking.h) \
    $(wildcard include/config/panic/timeout.h) \
    $(wildcard include/config/ring/buffer.h) \
  /home/administrator/Build/linux_repo/prebuilts/gcc/linux-x86/aarch64/aarch64-linux-android-4.9/lib/gcc/aarch64-linux-android/4.9.x-google/include/stdarg.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/linkage.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/stringify.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modversions.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/linkage.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/bitops.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/bitops.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/barrier.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/builtin-__ffs.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/builtin-ffs.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/builtin-__fls.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/builtin-fls.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/ffz.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/fls64.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/find.h \
    $(wildcard include/config/generic/find/first/bit.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/sched.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/hweight.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/arch_hweight.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/const_hweight.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/lock.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/non-atomic.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bitops/le.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/byteorder.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/byteorder/little_endian.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/byteorder/little_endian.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/swab.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/swab.h \
  arch/arm64/include/generated/asm/swab.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/swab.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/byteorder/generic.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/log2.h \
    $(wildcard include/config/arch/has/ilog2/u32.h) \
    $(wildcard include/config/arch/has/ilog2/u64.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/typecheck.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/printk.h \
    $(wildcard include/config/mt/printk/uart/console.h) \
    $(wildcard include/config/mt/eng/build.h) \
    $(wildcard include/config/log/too/much/warning.h) \
    $(wildcard include/config/message/loglevel/default.h) \
    $(wildcard include/config/early/printk.h) \
    $(wildcard include/config/printk.h) \
    $(wildcard include/config/dynamic/debug.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/init.h \
    $(wildcard include/config/broken/rodata.h) \
    $(wildcard include/config/lto.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kern_levels.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/cache.h \
    $(wildcard include/config/arch/has/cache/line/size.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/kernel.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/sysinfo.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/cache.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/cachetype.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/cputype.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dynamic_debug.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/stat.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/stat.h \
    $(wildcard include/config/compat.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/stat.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/stat.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/compat.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/sched.h \
    $(wildcard include/config/sched/debug.h) \
    $(wildcard include/config/prove/rcu.h) \
    $(wildcard include/config/no/hz/common.h) \
    $(wildcard include/config/lockup/detector.h) \
    $(wildcard include/config/detect/hung/task.h) \
    $(wildcard include/config/core/dump/default/elf/headers.h) \
    $(wildcard include/config/preempt/count.h) \
    $(wildcard include/config/sched/autogroup.h) \
    $(wildcard include/config/virt/cpu/accounting/native.h) \
    $(wildcard include/config/bsd/process/acct.h) \
    $(wildcard include/config/taskstats.h) \
    $(wildcard include/config/audit.h) \
    $(wildcard include/config/cgroups.h) \
    $(wildcard include/config/inotify/user.h) \
    $(wildcard include/config/fanotify.h) \
    $(wildcard include/config/epoll.h) \
    $(wildcard include/config/posix/mqueue.h) \
    $(wildcard include/config/keys.h) \
    $(wildcard include/config/perf/events.h) \
    $(wildcard include/config/schedstats.h) \
    $(wildcard include/config/task/delay/acct.h) \
    $(wildcard include/config/mtk/sched/cmp/tgs.h) \
    $(wildcard include/config/sched/smt.h) \
    $(wildcard include/config/disable/cpu/sched/domain/balance.h) \
    $(wildcard include/config/sched/mc.h) \
    $(wildcard include/config/numa.h) \
    $(wildcard include/config/mtk/sched/cmp.h) \
    $(wildcard include/config/sched/hmp.h) \
    $(wildcard include/config/sched/hmp/prio/filter.h) \
    $(wildcard include/config/hmp/tracer.h) \
    $(wildcard include/config/mtprof/cputime.h) \
    $(wildcard include/config/fair/group/sched.h) \
    $(wildcard include/config/mt/rt/throttle/mon.h) \
    $(wildcard include/config/rt/group/sched.h) \
    $(wildcard include/config/mt/sched/trace.h) \
    $(wildcard include/config/mt/sched/debug.h) \
    $(wildcard include/config/cgroup/sched.h) \
    $(wildcard include/config/preempt/notifiers.h) \
    $(wildcard include/config/blk/dev/io/trace.h) \
    $(wildcard include/config/preempt/rcu.h) \
    $(wildcard include/config/tree/preempt/rcu.h) \
    $(wildcard include/config/tasks/rcu.h) \
    $(wildcard include/config/compat/brk.h) \
    $(wildcard include/config/cc/stackprotector.h) \
    $(wildcard include/config/virt/cpu/accounting/gen.h) \
    $(wildcard include/config/swap.h) \
    $(wildcard include/config/sysvipc.h) \
    $(wildcard include/config/auditsyscall.h) \
    $(wildcard include/config/rt/mutexes.h) \
    $(wildcard include/config/debug/mutexes.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/lockdep.h) \
    $(wildcard include/config/block.h) \
    $(wildcard include/config/task/xacct.h) \
    $(wildcard include/config/cpusets.h) \
    $(wildcard include/config/futex.h) \
    $(wildcard include/config/debug/preempt.h) \
    $(wildcard include/config/numa/balancing.h) \
    $(wildcard include/config/fault/injection.h) \
    $(wildcard include/config/latencytop.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/memcg.h) \
    $(wildcard include/config/uprobes.h) \
    $(wildcard include/config/bcache.h) \
    $(wildcard include/config/preempt/monitor.h) \
    $(wildcard include/config/cpumask/offstack.h) \
    $(wildcard include/config/have/unstable/sched/clock.h) \
    $(wildcard include/config/irq/time/accounting.h) \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/no/hz/full.h) \
    $(wildcard include/config/proc/fs.h) \
    $(wildcard include/config/stack/growsup.h) \
    $(wildcard include/config/debug/stack/usage.h) \
    $(wildcard include/config/preempt.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/sched.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/sched/prio.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/param.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/param.h \
    $(wildcard include/config/hz.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/param.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/capability.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/capability.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/threads.h \
    $(wildcard include/config/nr/cpus.h) \
    $(wildcard include/config/base/small.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/timex.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/timex.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/time.h \
    $(wildcard include/config/arch/uses/gettimeoffset.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/seqlock.h \
    $(wildcard include/config/debug/lock/alloc.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/spinlock.h \
    $(wildcard include/config/debug/spinlock.h) \
    $(wildcard include/config/generic/lockbreak.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/preempt.h \
    $(wildcard include/config/preempt/tracer.h) \
    $(wildcard include/config/context/tracking.h) \
  arch/arm64/include/generated/asm/preempt.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/preempt.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/thread_info.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/bug.h \
  arch/arm64/include/generated/asm/bug.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/bug.h \
    $(wildcard include/config/bug.h) \
    $(wildcard include/config/generic/bug/relative/pointers.h) \
    $(wildcard include/config/debug/bugverbose.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/thread_info.h \
    $(wildcard include/config/arm64/64k/pages.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/irqflags.h \
    $(wildcard include/config/mtprof.h) \
    $(wildcard include/config/irqsoff/tracer.h) \
    $(wildcard include/config/trace/irqflags/support.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/irqflags.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/ptrace.h \
    $(wildcard include/config/cpu/big/endian.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/ptrace.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/hwcap.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/hwcap.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/bottom_half.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/preempt_mask.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/spinlock_types.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/spinlock_types.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/lockdep.h \
    $(wildcard include/config/lock/stat.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rwlock_types.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/spinlock.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/processor.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/string.h \
    $(wildcard include/config/binary/printf.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/string.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/string.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/fpsimd.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/hw_breakpoint.h \
    $(wildcard include/config/have/hw/breakpoint.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rwlock.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/spinlock_api_smp.h \
    $(wildcard include/config/inline/spin/lock.h) \
    $(wildcard include/config/inline/spin/lock/bh.h) \
    $(wildcard include/config/inline/spin/lock/irq.h) \
    $(wildcard include/config/inline/spin/lock/irqsave.h) \
    $(wildcard include/config/inline/spin/trylock.h) \
    $(wildcard include/config/inline/spin/trylock/bh.h) \
    $(wildcard include/config/uninline/spin/unlock.h) \
    $(wildcard include/config/inline/spin/unlock/bh.h) \
    $(wildcard include/config/inline/spin/unlock/irq.h) \
    $(wildcard include/config/inline/spin/unlock/irqrestore.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rwlock_api_smp.h \
    $(wildcard include/config/inline/read/lock.h) \
    $(wildcard include/config/inline/write/lock.h) \
    $(wildcard include/config/inline/read/lock/bh.h) \
    $(wildcard include/config/inline/write/lock/bh.h) \
    $(wildcard include/config/inline/read/lock/irq.h) \
    $(wildcard include/config/inline/write/lock/irq.h) \
    $(wildcard include/config/inline/read/lock/irqsave.h) \
    $(wildcard include/config/inline/write/lock/irqsave.h) \
    $(wildcard include/config/inline/read/trylock.h) \
    $(wildcard include/config/inline/write/trylock.h) \
    $(wildcard include/config/inline/read/unlock.h) \
    $(wildcard include/config/inline/write/unlock.h) \
    $(wildcard include/config/inline/read/unlock/bh.h) \
    $(wildcard include/config/inline/write/unlock/bh.h) \
    $(wildcard include/config/inline/read/unlock/irq.h) \
    $(wildcard include/config/inline/write/unlock/irq.h) \
    $(wildcard include/config/inline/read/unlock/irqrestore.h) \
    $(wildcard include/config/inline/write/unlock/irqrestore.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/atomic.h \
    $(wildcard include/config/arch/has/atomic/or.h) \
    $(wildcard include/config/generic/atomic64.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/atomic.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/cmpxchg.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/atomic-long.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/math64.h \
    $(wildcard include/config/arch/supports/int128.h) \
  arch/arm64/include/generated/asm/div64.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/div64.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/time64.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/time.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/param.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/timex.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/arch_timer.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/clocksource/arm_arch_timer.h \
    $(wildcard include/config/arm/arch/timer.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/clocksource.h \
    $(wildcard include/config/arch/clocksource/data.h) \
    $(wildcard include/config/clocksource/watchdog.h) \
    $(wildcard include/config/clksrc/of.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/timer.h \
    $(wildcard include/config/timer/stats.h) \
    $(wildcard include/config/debug/objects/timers.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/ktime.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/jiffies.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/timekeeping.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/debugobjects.h \
    $(wildcard include/config/debug/objects.h) \
    $(wildcard include/config/debug/objects/free.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/io.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/blk_types.h \
    $(wildcard include/config/blk/cgroup.h) \
    $(wildcard include/config/blk/dev/integrity.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/pgtable.h \
    $(wildcard include/config/transparent/hugepage.h) \
    $(wildcard include/config/have/rcu/table/free.h) \
    $(wildcard include/config/arm64/pgtable/levels.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/proc-fns.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/page.h \
    $(wildcard include/config/have/arch/pfn/valid.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/pgtable-types.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/pgtable-nopud.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/memory.h \
    $(wildcard include/config/arm64/va/bits.h) \
  arch/arm64/include/generated/asm/sizes.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/sizes.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/sizes.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/memory_model.h \
    $(wildcard include/config/flatmem.h) \
    $(wildcard include/config/discontigmem.h) \
    $(wildcard include/config/sparsemem/vmemmap.h) \
    $(wildcard include/config/sparsemem.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/getorder.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/pgtable-hwdef.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/pgtable.h \
    $(wildcard include/config/have/arch/soft/dirty.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/mm_types.h \
    $(wildcard include/config/split/ptlock/cpus.h) \
    $(wildcard include/config/arch/enable/split/pmd/ptlock.h) \
    $(wildcard include/config/have/cmpxchg/double.h) \
    $(wildcard include/config/have/aligned/struct/page.h) \
    $(wildcard include/config/want/page/debug/flags.h) \
    $(wildcard include/config/kmemcheck.h) \
    $(wildcard include/config/aio.h) \
    $(wildcard include/config/mmu/notifier.h) \
    $(wildcard include/config/compaction.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/auxvec.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/auxvec.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/auxvec.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rbtree.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rwsem.h \
    $(wildcard include/config/rwsem/spin/on/owner.h) \
    $(wildcard include/config/rwsem/generic/spinlock.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/osq_lock.h \
  arch/arm64/include/generated/asm/rwsem.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/rwsem.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/completion.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/wait.h \
  arch/arm64/include/generated/asm/current.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/current.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/wait.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/cpumask.h \
    $(wildcard include/config/debug/per/cpu/maps.h) \
    $(wildcard include/config/disable/obsolete/cpumask/functions.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/bitmap.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/page-debug-flags.h \
    $(wildcard include/config/page/poisoning.h) \
    $(wildcard include/config/page/guard.h) \
    $(wildcard include/config/page/debug/something/else.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/uprobes.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/errno.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/errno.h \
  arch/arm64/include/generated/asm/errno.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/errno.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/errno-base.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/page-flags-layout.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/numa.h \
    $(wildcard include/config/nodes/shift.h) \
  include/generated/bounds.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/sparsemem.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/mmu.h \
  arch/arm64/include/generated/asm/early_ioremap.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/early_ioremap.h \
    $(wildcard include/config/generic/early/ioremap.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/alternative.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/cpufeature.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/xen/xen.h \
    $(wildcard include/config/xen.h) \
    $(wildcard include/config/xen/dom0.h) \
    $(wildcard include/config/xen/pvh.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/iomap.h \
    $(wildcard include/config/has/ioport/map.h) \
    $(wildcard include/config/pci.h) \
    $(wildcard include/config/generic/iomap.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/pci_iomap.h \
    $(wildcard include/config/no/generic/pci/ioport/map.h) \
    $(wildcard include/config/generic/pci/iomap.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/timex.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/plist.h \
    $(wildcard include/config/debug/pi/list.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/nodemask.h \
    $(wildcard include/config/highmem.h) \
    $(wildcard include/config/movable/node.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/cputime.h \
  arch/arm64/include/generated/asm/cputime.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/cputime.h \
    $(wildcard include/config/virt/cpu/accounting.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/cputime_jiffies.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/smp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/llist.h \
    $(wildcard include/config/arch/have/nmi/safe/cmpxchg.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/smp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/sem.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rcupdate.h \
    $(wildcard include/config/tree/rcu.h) \
    $(wildcard include/config/rcu/trace.h) \
    $(wildcard include/config/rcu/stall/common.h) \
    $(wildcard include/config/rcu/user/qs.h) \
    $(wildcard include/config/rcu/nocb/cpu.h) \
    $(wildcard include/config/tiny/rcu.h) \
    $(wildcard include/config/debug/objects/rcu/head.h) \
    $(wildcard include/config/rcu/boost.h) \
    $(wildcard include/config/rcu/nocb/cpu/all.h) \
    $(wildcard include/config/no/hz/full/sysidle.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rcutree.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/sem.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/ipc.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/uidgid.h \
    $(wildcard include/config/user/ns.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/highuid.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/ipc.h \
  arch/arm64/include/generated/asm/ipcbuf.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/ipcbuf.h \
  arch/arm64/include/generated/asm/sembuf.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/sembuf.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/shm.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/shm.h \
  arch/arm64/include/generated/asm/shmbuf.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/shmbuf.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/shmparam.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/shmparam.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/signal.h \
    $(wildcard include/config/old/sigaction.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/signal.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/signal.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/signal.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/signal.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/signal-defs.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/sigcontext.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/siginfo.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/siginfo.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/siginfo.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/pid.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/percpu.h \
    $(wildcard include/config/need/per/cpu/embed/first/chunk.h) \
    $(wildcard include/config/need/per/cpu/page/first/chunk.h) \
    $(wildcard include/config/have/setup/per/cpu/area.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/mmdebug.h \
    $(wildcard include/config/debug/vm.h) \
    $(wildcard include/config/debug/virtual.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/pfn.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/percpu.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/percpu.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/percpu-defs.h \
    $(wildcard include/config/debug/force/weak/per/cpu.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/topology.h \
    $(wildcard include/config/use/percpu/numa/node/id.h) \
    $(wildcard include/config/have/memoryless/nodes.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/mmzone.h \
    $(wildcard include/config/force/max/zoneorder.h) \
    $(wildcard include/config/cma.h) \
    $(wildcard include/config/memory/isolation.h) \
    $(wildcard include/config/zone/dma.h) \
    $(wildcard include/config/zone/dma32.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/have/memblock/node/map.h) \
    $(wildcard include/config/flat/node/mem/map.h) \
    $(wildcard include/config/no/bootmem.h) \
    $(wildcard include/config/have/memory/present.h) \
    $(wildcard include/config/need/node/memmap/size.h) \
    $(wildcard include/config/need/multiple/nodes.h) \
    $(wildcard include/config/have/arch/early/pfn/to/nid.h) \
    $(wildcard include/config/sparsemem/extreme.h) \
    $(wildcard include/config/nodes/span/other/nodes.h) \
    $(wildcard include/config/holes/in/zone.h) \
    $(wildcard include/config/arch/has/holes/memorymodel.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/pageblock-flags.h \
    $(wildcard include/config/hugetlb/page.h) \
    $(wildcard include/config/hugetlb/page/size/variable.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/memory_hotplug.h \
    $(wildcard include/config/memory/hotremove.h) \
    $(wildcard include/config/have/arch/nodedata/extension.h) \
    $(wildcard include/config/have/bootmem/info/node.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/notifier.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/mutex.h \
    $(wildcard include/config/mutex/spin/on/owner.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/srcu.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/workqueue.h \
    $(wildcard include/config/debug/objects/work.h) \
    $(wildcard include/config/freezer.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/topology.h \
    $(wildcard include/config/arm/cpu/topology.h) \
    $(wildcard include/config/mtk/cpu/topology.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/topology.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/proportions.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/percpu_counter.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/gfp.h \
    $(wildcard include/config/pm/sleep.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/seccomp.h \
    $(wildcard include/config/seccomp.h) \
    $(wildcard include/config/have/arch/seccomp/filter.h) \
    $(wildcard include/config/seccomp/filter.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/seccomp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/seccomp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/unistd.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/unistd.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/unistd.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/unistd.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/seccomp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/unistd.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rculist.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rtmutex.h \
    $(wildcard include/config/debug/rt/mutexes.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/resource.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/resource.h \
  arch/arm64/include/generated/asm/resource.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/resource.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/resource.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/hrtimer.h \
    $(wildcard include/config/high/res/timers.h) \
    $(wildcard include/config/timerfd.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/timerqueue.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/task_io_accounting.h \
    $(wildcard include/config/task/io/accounting.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/latencytop.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/cred.h \
    $(wildcard include/config/debug/credentials.h) \
    $(wildcard include/config/security.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/key.h \
    $(wildcard include/config/sysctl.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/sysctl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/sysctl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/assoc_array.h \
    $(wildcard include/config/associative/array.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/selinux.h \
    $(wildcard include/config/security/selinux.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/magic.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/ptrace.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/err.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/pid_namespace.h \
    $(wildcard include/config/pid/ns.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/mm.h \
    $(wildcard include/config/mem/soft/dirty.h) \
    $(wildcard include/config/x86.h) \
    $(wildcard include/config/ppc.h) \
    $(wildcard include/config/parisc.h) \
    $(wildcard include/config/metag.h) \
    $(wildcard include/config/ia64.h) \
    $(wildcard include/config/ksm.h) \
    $(wildcard include/config/shmem.h) \
    $(wildcard include/config/debug/vm/rb.h) \
    $(wildcard include/config/debug/pagealloc.h) \
    $(wildcard include/config/hibernation.h) \
    $(wildcard include/config/hugetlbfs.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/debug_locks.h \
    $(wildcard include/config/debug/locking/api/selftests.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/range.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/bit_spinlock.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/shrinker.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/page-flags.h \
    $(wildcard include/config/pageflags/extended.h) \
    $(wildcard include/config/arch/uses/pg/uncached.h) \
    $(wildcard include/config/memory/failure.h) \
    $(wildcard include/config/toi/incremental.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/huge_mm.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/vmstat.h \
    $(wildcard include/config/vm/event/counters.h) \
    $(wildcard include/config/debug/tlbflush.h) \
    $(wildcard include/config/debug/vm/vmacache.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/vm_event_item.h \
    $(wildcard include/config/migration.h) \
    $(wildcard include/config/memory/balloon.h) \
    $(wildcard include/config/balloon/compaction.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/nsproxy.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kref.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/ptrace.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/stat.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kmod.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/elf.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/elf.h \
  arch/arm64/include/generated/asm/user.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/user.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/elf.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/elf-em.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kobject.h \
    $(wildcard include/config/uevent/helper.h) \
    $(wildcard include/config/debug/kobject/release.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/sysfs.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kernfs.h \
    $(wildcard include/config/kernfs.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/idr.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kobject_ns.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/moduleparam.h \
    $(wildcard include/config/alpha.h) \
    $(wildcard include/config/ppc64.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/jump_label.h \
    $(wildcard include/config/jump/label.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/module.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/module.h \
    $(wildcard include/config/have/mod/arch/specific.h) \
    $(wildcard include/config/modules/use/elf/rel.h) \
    $(wildcard include/config/modules/use/elf/rela.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/netfilter_ipv4.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/netfilter_ipv4.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/netfilter.h \
    $(wildcard include/config/netfilter.h) \
    $(wildcard include/config/nf/nat/needed.h) \
    $(wildcard include/config/nf/conntrack.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/skbuff.h \
    $(wildcard include/config/xfrm.h) \
    $(wildcard include/config/ipv6/ndisc/nodetype.h) \
    $(wildcard include/config/net/sched.h) \
    $(wildcard include/config/net/cls/act.h) \
    $(wildcard include/config/net/rx/busy/poll.h) \
    $(wildcard include/config/network/secmark.h) \
    $(wildcard include/config/network/phy/timestamping.h) \
    $(wildcard include/config/netfilter/xt/target/trace.h) \
    $(wildcard include/config/nf/tables.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kmemcheck.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/net.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/random.h \
    $(wildcard include/config/arch/random.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/random.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/ioctl.h \
  arch/arm64/include/generated/asm/ioctl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/ioctl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/ioctl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/irqnr.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/irqnr.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/fcntl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/fcntl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/uapi/asm/fcntl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/fcntl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/net.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/socket.h \
  arch/arm64/include/generated/asm/socket.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/socket.h \
  arch/arm64/include/generated/asm/sockios.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/sockios.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/sockios.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/uio.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/uio.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/socket.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/textsearch.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/slab.h \
    $(wildcard include/config/slab/debug.h) \
    $(wildcard include/config/failslab.h) \
    $(wildcard include/config/memcg/kmem.h) \
    $(wildcard include/config/slab.h) \
    $(wildcard include/config/slub.h) \
    $(wildcard include/config/slob.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kmemleak.h \
    $(wildcard include/config/debug/kmemleak.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/checksum.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/uaccess.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/compiler.h \
  arch/arm64/include/generated/asm/checksum.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/checksum.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dma-mapping.h \
    $(wildcard include/config/has/dma.h) \
    $(wildcard include/config/arch/has/dma/set/coherent/mask.h) \
    $(wildcard include/config/have/dma/attrs.h) \
    $(wildcard include/config/need/dma/map/state.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/device.h \
    $(wildcard include/config/debug/devres.h) \
    $(wildcard include/config/acpi.h) \
    $(wildcard include/config/pinctrl.h) \
    $(wildcard include/config/dma/cma.h) \
    $(wildcard include/config/devtmpfs.h) \
    $(wildcard include/config/sysfs/deprecated.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/ioport.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/klist.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/pinctrl/devinfo.h \
    $(wildcard include/config/pm.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/pinctrl/consumer.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/seq_file.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/pinctrl/pinctrl-state.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/pm.h \
    $(wildcard include/config/vt/console/sleep.h) \
    $(wildcard include/config/pm/runtime.h) \
    $(wildcard include/config/pm/clk.h) \
    $(wildcard include/config/pm/generic/domains.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/ratelimit.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/device.h \
    $(wildcard include/config/iommu/api.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/pm_wakeup.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dma-attrs.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dma-direction.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/scatterlist.h \
    $(wildcard include/config/debug/sg.h) \
    $(wildcard include/config/arch/has/sg/chain.h) \
  arch/arm64/include/generated/asm/scatterlist.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/scatterlist.h \
    $(wildcard include/config/need/sg/dma/length.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/dma-mapping.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/vmalloc.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/dma-coherent.h \
    $(wildcard include/config/have/generic/dma/coherent.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/xen/hypervisor.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/../../arm/include/asm/xen/hypervisor.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/dma-mapping-common.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dma-debug.h \
    $(wildcard include/config/dma/api/debug.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/netdev_features.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/flow_keys.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/if.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/hdlc/ioctl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/in.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/in.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/in6.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/in6.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/libc-compat.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/static_key.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/netfilter.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/flow.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/netdevice.h \
    $(wildcard include/config/dcb.h) \
    $(wildcard include/config/wlan.h) \
    $(wildcard include/config/ax25.h) \
    $(wildcard include/config/mac80211/mesh.h) \
    $(wildcard include/config/net/ipip.h) \
    $(wildcard include/config/net/ipgre.h) \
    $(wildcard include/config/ipv6/sit.h) \
    $(wildcard include/config/ipv6/tunnel.h) \
    $(wildcard include/config/rps.h) \
    $(wildcard include/config/netpoll.h) \
    $(wildcard include/config/xps.h) \
    $(wildcard include/config/bql.h) \
    $(wildcard include/config/rfs/accel.h) \
    $(wildcard include/config/fcoe.h) \
    $(wildcard include/config/net/poll/controller.h) \
    $(wildcard include/config/libfcoe.h) \
    $(wildcard include/config/wireless/ext.h) \
    $(wildcard include/config/vlan/8021q.h) \
    $(wildcard include/config/net/dsa.h) \
    $(wildcard include/config/tipc.h) \
    $(wildcard include/config/net/ns.h) \
    $(wildcard include/config/cgroup/net/prio.h) \
    $(wildcard include/config/net/flow/limit.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/pm_qos.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/miscdevice.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/major.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/delay.h \
  arch/arm64/include/generated/asm/delay.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/delay.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/prefetch.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dmaengine.h \
    $(wildcard include/config/async/tx/enable/channel/switch.h) \
    $(wildcard include/config/dma/engine.h) \
    $(wildcard include/config/rapidio/dma/engine.h) \
    $(wildcard include/config/async/tx/dma.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dynamic_queue_limits.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/ethtool.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/compat.h \
    $(wildcard include/config/compat/old/sigaction.h) \
    $(wildcard include/config/odd/rt/sigaction.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/fs.h \
    $(wildcard include/config/fs/posix/acl.h) \
    $(wildcard include/config/ima.h) \
    $(wildcard include/config/quota.h) \
    $(wildcard include/config/fsnotify.h) \
    $(wildcard include/config/file/locking.h) \
    $(wildcard include/config/fs/xip.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/kdev_t.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/kdev_t.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dcache.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rculist_bl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/list_bl.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/lockref.h \
    $(wildcard include/config/arch/use/cmpxchg/lockref.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/path.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/list_lru.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/radix-tree.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/semaphore.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/fiemap.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/migrate_mode.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/percpu-rwsem.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/fs.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/limits.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/quota.h \
    $(wildcard include/config/quota/netlink/interface.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/dqblk_xfs.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dqblk_v1.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dqblk_v2.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/dqblk_qtree.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/projid.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/quota.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/nfs_fs_i.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/aio_abi.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/ethtool.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/if_ether.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/if_ether.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/net_namespace.h \
    $(wildcard include/config/ipv6.h) \
    $(wildcard include/config/ieee802154/6lowpan.h) \
    $(wildcard include/config/ip/sctp.h) \
    $(wildcard include/config/ip/dccp.h) \
    $(wildcard include/config/nf/defrag/ipv6.h) \
    $(wildcard include/config/wext/core.h) \
    $(wildcard include/config/ip/vs.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/core.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/mib.h \
    $(wildcard include/config/xfrm/statistics.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/snmp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/snmp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/u64_stats_sync.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/unix.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/packet.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/ipv4.h \
    $(wildcard include/config/ip/multiple/tables.h) \
    $(wildcard include/config/ip/route/classid.h) \
    $(wildcard include/config/ip/mroute.h) \
    $(wildcard include/config/ip/mroute/multiple/tables.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/inet_frag.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/ipv6.h \
    $(wildcard include/config/ipv6/multiple/tables.h) \
    $(wildcard include/config/ipv6/mroute.h) \
    $(wildcard include/config/ipv6/mroute/multiple/tables.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/dst_ops.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/ieee802154_6lowpan.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/sctp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/dccp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/netfilter.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/proc_fs.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/x_tables.h \
    $(wildcard include/config/bridge/nf/ebtables.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/conntrack.h \
    $(wildcard include/config/nf/conntrack/proc/compat.h) \
    $(wildcard include/config/nf/conntrack/events.h) \
    $(wildcard include/config/nf/conntrack/labels.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/list_nulls.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/netfilter/nf_conntrack_tcp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/netfilter/nf_conntrack_tcp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/nftables.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/xfrm.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/xfrm.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/flowcache.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/interrupt.h \
    $(wildcard include/config/irq/forced/threading.h) \
    $(wildcard include/config/generic/irq/probe.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/irqreturn.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/hardirq.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/ftrace_irq.h \
    $(wildcard include/config/ftrace/nmi/enter.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/vtime.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/context_tracking_state.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/hardirq.h \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/irq.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/irq.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/irq_cpustat.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/seq_file_net.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/dsa.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/of.h \
    $(wildcard include/config/sparc.h) \
    $(wildcard include/config/of/dynamic.h) \
    $(wildcard include/config/of.h) \
    $(wildcard include/config/attach/node.h) \
    $(wildcard include/config/detach/node.h) \
    $(wildcard include/config/add/property.h) \
    $(wildcard include/config/remove/property.h) \
    $(wildcard include/config/update/property.h) \
    $(wildcard include/config/of/resolve.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/mod_devicetable.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/uuid.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/uuid.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/property.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/phy.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/mii.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/mii.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/phy_fixed.h \
    $(wildcard include/config/fixed/phy.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netprio_cgroup.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/cgroup.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/cgroupstats.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/taskstats.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/percpu-refcount.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/cgroup_subsys.h \
    $(wildcard include/config/cgroup/cpuacct.h) \
    $(wildcard include/config/cgroup/device.h) \
    $(wildcard include/config/cgroup/freezer.h) \
    $(wildcard include/config/cgroup/net/classid.h) \
    $(wildcard include/config/cgroup/perf.h) \
    $(wildcard include/config/cgroup/hugetlb.h) \
    $(wildcard include/config/cgroup/debug.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/neighbour.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/netlink.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/scm.h \
    $(wildcard include/config/security/network.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/security.h \
    $(wildcard include/config/fw/loader/user/helper.h) \
    $(wildcard include/config/security/path.h) \
    $(wildcard include/config/security/network/xfrm.h) \
    $(wildcard include/config/securityfs.h) \
    $(wildcard include/config/security/yama.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/netlink.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/netdevice.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/if_packet.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/if_link.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/if_link.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/inetdevice.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/ip.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/ip.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rtnetlink.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/rtnetlink.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/if_addr.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/genetlink.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/genetlink.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/genetlink.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netlink.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/tcp.h \
    $(wildcard include/config/tcp/md5sig.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/sock.h \
    $(wildcard include/config/net.h) \
    $(wildcard include/config/inet.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/uaccess.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/memcontrol.h \
    $(wildcard include/config/memcg/swap.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/res_counter.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/aio.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/filter.h \
    $(wildcard include/config/bpf/jit.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/arch/arm64/include/asm/cacheflush.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/filter.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/bpf_common.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/bpf.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/rculist_nulls.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/poll.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/poll.h \
  arch/arm64/include/generated/asm/poll.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/asm-generic/poll.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/dst.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/neighbour.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/rtnetlink.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/tcp_states.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/net_tstamp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/inet_connection_sock.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/inet_sock.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/jhash.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/unaligned/packed_struct.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/request_sock.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netns/hash.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/inet_timewait_sock.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/timewait_sock.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/tcp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/udp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/udp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/icmp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/icmp.h \
  include/generated/uapi/linux/version.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/ip.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/route.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/inetpeer.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/ipv6.h \
    $(wildcard include/config/have/efficient/unaligned/access.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/ipv6.h \
    $(wildcard include/config/ipv6/router/pref.h) \
    $(wildcard include/config/ipv6/route/info.h) \
    $(wildcard include/config/ipv6/optimistic/dad.h) \
    $(wildcard include/config/ipv6/mip6.h) \
    $(wildcard include/config/ipv6/subtrees.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/ipv6.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/icmpv6.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/icmpv6.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/if_inet6.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/ndisc.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/if_arp.h \
    $(wildcard include/config/firewire/net.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/if_arp.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/hash.h \
    $(wildcard include/config/arch/has/fast/multiplier.h) \
  arch/arm64/include/generated/asm/hash.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/asm-generic/hash.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/in_route.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/uapi/linux/route.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/tcp.h \
    $(wildcard include/config/syn/cookies.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/crypto.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/linux/cryptohash.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/inet_hashtables.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/inet_ecn.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/dsfield.h \
  /home/administrator/Build/linux_repo/kernel-3.18/include/net/netfilter/nf_queue.h \
    $(wildcard include/config/ip6/nf/iptables.h) \
  /home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/ItsOnAPI.h \

/home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/ItsOnAPI.o: $(deps_/home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/ItsOnAPI.o)

$(deps_/home/administrator/Build/linux_repo/kernel-3.18/drivers/misc/mediatek/itson/arm64/itson/ItsOnAPI.o):

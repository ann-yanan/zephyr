# Copyright (C) 2017-2024 Alibaba Group Holding Limited
# SPDX-License-Identifier: Apache-2.0

add_subdirectory(${SOC_SERIES})

#override mabi&march in zephyr compile system for xuantie cpu
#can't use -mcpu instead
if(CONFIG_CPU_XUANTIE_C908V)
  add_subdirectory(cpu/c908v)
#elseif(CONFIG_CPU_XUANTIE_C908)
  #add_subdirectory(cpu/c908)
endif()

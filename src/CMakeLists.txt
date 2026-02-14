add_executable(main main.c)
generate_object(main .hex ihex)
target_link_libraries(
    main
    stm32_system
    stm32_ll
)

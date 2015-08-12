/* Linker script to configure memory regions. 
 * Need modifying for a specific board. 
 *   FLASH.ORIGIN: starting address of flash
 *   FLASH.LENGTH: length of flash
 *   SWAP.ORIGIN: starting address of swap area
 *   SWAP.LENGTH: length of swap area
 *   SRAM_L.ORIGIN: starting address of lower SRAM
 *   SRAM_L.LENGTH: length of lower SRAM
 *   SRAM.ORIGIN: starting address of SRAM
 *   SRAM.LENGTH: length of SRAM */
MEMORY
{
    FLASH  (rx)   : ORIGIN = 0x00000000, LENGTH = 510K
    SWAP   (rx)   : ORIGIN = 0x0003F800, LENGTH = 2K
    SRAM_L (rwx)  : ORIGIN = 0x1FFF0000, LENGTH = 64K
    SRAM   (rwx)  : ORIGIN = 0x20000000, LENGTH = 64K
}

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory regions FLASH and SRAM.
 * It references following symbols, which must be defined in code: */
SECTIONS
{
    .entry :
    {
        _vector_rom = .;
	*(.vector_table)
	*(.default_handlers)
    } > FLASH
    
    .text :
    {
        . = ALIGN(4);
	_text_load = LOADADDR(.text);
        _text_start = .;
        *(.text*)
	*(.rodata*)
	. = ALIGN(4);
	_text_end = .;
    } > FLASH

    .ramcode :
    {
        . = ALIGN(4);
	_ramcode_load = LOADADDR(.ramcode);
	_ramcode_start = .;
	*(.ramcode*)
	. = ALIGN(4);
	_ramcode_end = .;
    } > SRAM_L AT > FLASH

    .flashSwap :
    {
        _flash_swap_addr = .;
    } > SWAP

    .ramvect :
    {
        . = ALIGN(4);
	_vector_ram_start = .;
	. = _vector_ram_start + 0x400;
	_vector_ram_end = .;
    } > SRAM

    .data :
    {
        . = ALIGN(4);
	_data_load = LOADADDR(.data);
        _data_start = .;
	*(.data*)
	. = ALIGN(4);
	_data_end = .;
    } > SRAM AT > FLASH

    .bss :
    {
        . = ALIGN(4);
        _bss_start = .;
	*(.bss*)
	. = ALIGN(4);
	_bss_end = .;
	_heap_start = .;
    } > SRAM

    STACK_SIZE = 16K;
    _stack_start = ALIGN(ORIGIN(SRAM) + LENGTH(SRAM), 8);
    _stack_end = _stack_start - STACK_SIZE;
    _heap_end = ALIGN(ORIGIN(SRAM) + LENGTH(SRAM) - STACK_SIZE, 8);
    _process_stack_start = _stack_end;
    _process_stack_end = _process_stack_start - STACK_SIZE;

    _memory_base = _heap_start;
    _memory_end = heap_end;
}

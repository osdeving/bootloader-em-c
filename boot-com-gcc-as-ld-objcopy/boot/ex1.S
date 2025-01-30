/*
Exemplo simples de bootcode usando o gas.
ex1.S - 28/05/2014
 
 Este exemplo apenas entra em loop infinito, mas serve pra testar as
 ferramentas de desenvolvimento e teste (binutils/coreutils/bochs)

 Gera um binário puro (ex1.bin) de 512 bytes pronto para ir pro setor 1.
 
$ as ex1.S -o ex1.o
$ ld -Ttext 0x7c00 --oformat=binary ex1.o -o ex1.bin

 Cria uma imagem (floppy.img) vazia e coloca ex1.bin no primeiro setor.
 
$ dd if=/dev/zero of=floppy.img bs=512 count=2880
$ dd if=ex1.bin of=floppy.img conv=notrunc

 Usa o bochs para testar (só instale se precisar).
 Cria um .txt de configuração.

# apt-get install bochs-x
$ echo "floppya: 1_44=floppy.img, status=inserted" > bochsrc.txt
$ bochs -f bochsrc.txt

 Funcionou aqui no Windows. Se o bochsrc.txt não funcionar aí, tente
 acrescentar:

# use sdl abaixo se x não funcionar
display_library: x 
# a variável $BXHSARE deve existir
romimage: file=$BXSHARE/BIOS-bochs-latest 
vgaromimage: file=$BXSHARE/VGABIOS-lgpl-latest
# use se quiser direcionar log para um arquivo
log: bochsout.log 

 Veja mais opções na documentação do bochs.
*/ 

// código de 16 bits (8086)
// nota: as diretivas do gas usam o prefixo ponto (.)
.code16

// área de código
.text

// exporta o rótulo _start
.global _start

// byte 0 do arquivo, endereço 0x7c00 (opção: -Ttext 0x7c00 do ld)
_start:
	
	//laço infinito
	// nota: o operador '.' tem função semelhante do operador '$' do nasm
	jmp . 
	
	// move para o byte 510 do arquivo (será o endereço 0x7c00+510)
	. = _start + 510
	
	// coloca o byte 1 da assinatura de boot em 510
	// nota: usamos .byte/.word/.long/.quad em vez de db/dw/dd/dq do nasm
	.byte 0x55
	
	// coloca o byte 2 da assinatura de boot em 511
	.byte 0xAA

// byte 512, fim...



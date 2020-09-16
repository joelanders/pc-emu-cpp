//
// Created by Joe Landers on 23.05.20.
//

#include "Registers.h"

Registers::Registers()
    : eax(0), ecx(0), edx(0), ebx(0), esp(0), ebp(0), esi(0), edi(0), eip(0), ss(0), cs(0), ds(0), es(0), fs(0), gs(0),
      cf(0), pf(0), af(0), zf(0), sf(0), of(0) {
}

std::ostream&
operator<<(std::ostream& os, const Registers& registers) {
    os << "Registers:" << std::endl;
    os << "\teax: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_eax() << std::endl;
    os << "\tecx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ecx() << std::endl;
    os << "\tedx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_edx() << std::endl;
    os << "\tebx: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ebx() << std::endl;

    os << "\tesp: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_esp() << std::endl;
    os << "\tebp: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ebp() << std::endl;
    os << "\tesi: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_esi() << std::endl;
    os << "\tedi: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_edi() << std::endl;

    os << "\teip: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_eip() << std::endl;

    os << "\tss: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ss() << std::endl;
    os << "\tcs: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_cs() << std::endl;
    os << "\tds: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_ds() << std::endl;
    os << "\tes: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_es() << std::endl;
    os << "\tfs: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_fs() << std::endl;
    os << "\tgs: ";
    os << std::setfill('0') << std::setw(8) << std::hex << registers.get_gs() << std::endl;
    return os;
}

bool
    Registers::set_segment_register(Register reg, uint32_t value) {
    switch (reg) {
    case Ss:
        ss = value;
        return true;
    case Cs:
        cs = value;
        return true;
    case Ds:
        ds = value;
        return true;
    case Es:
        es = value;
        return true;
    case Fs:
        fs = value;
        return true;
    case Gs:
        gs = value;
        return true;
    }
    throw std::runtime_error("set_segment_register() failed");
}

// XXX look up "implicit registers" (Eip and Esp) -- 16 bit or 32 bit dep. on segment descriptor
// The effect of the Big flag is subtle: it influences things like in Code Segments the size of the value pushed during
// a CALL, and in Data Segments the Segment wrap for Stacks - if ESP is 0000_0000h, a PUSH EAX will make ESP either
// 0000_FFFCh or FFFF_FFFCh depending on that flag - which doesn't mean much until you get to Expand Down Segments.
bool
Registers::set_register(Width w, Register reg, uint32_t value, bool silent) {
    uint32_t mask;
    switch (w) {
    case U8:
        mask = 0xff;
        break;
    case U16:
        mask = 0xffff;
        break;
    case U32:
        mask = 0xffffffff;
        break;
    }

    // XXX is this the right place to chomp the extra bits? make caller do it?
    if (!silent) {
        // std::cout << "REGSET offset: " << std::to_string(register_to_index(reg));
        std::cout << "REGSET ";
        print_register(reg, w);
        std::cout << " value: ";
        print_quad_in_hex(value & mask);
        printf("\n");
    }

    if (w == U8) {
        switch (reg) {
        case Al:
            eax = (eax & ~0xff) | (value & 0xff);
            return true;
        case Cl:
            ecx = (ecx & ~0xff) | (value & 0xff);
            return true;
        case Dl:
            edx = (edx & ~0xff) | (value & 0xff);
            return true;
        case Bl:
            ebx = (ebx & ~0xff) | (value & 0xff);
            return true;
        case Ah:
            eax = (eax & ~0xff00) | ((value << 8) & 0xff00);
            return true;
        case Ch:
            ecx = (ecx & ~0xff00) | ((value << 8) & 0xff00);
            return true;
        case Dh:
            edx = (edx & ~0xff00) | ((value << 8) & 0xff00);
            return true;
        case Bh:
            ebx = (ebx & ~0xff00) | ((value << 8) & 0xff00);
            return true;
        }
        throw std::runtime_error("set_register: 8-bit width but not one of the general registers?");
    }

    switch (reg) {
    case Eax:
        eax = (eax & ~mask) | (value & mask);
        return true;
    case Ecx:
        ecx = (ecx & ~mask) | (value & mask);
        return true;
    case Edx:
        edx = (edx & ~mask) | (value & mask);
        return true;
    case Ebx:
        ebx = (ebx & ~mask) | (value & mask);
        return true;
    case Esp:
        esp = (esp & ~mask) | (value & mask);
        return true;
    case Ebp:
        ebp = (ebp & ~mask) | (value & mask);
        return true;
    case Esi:
        esi = (esi & ~mask) | (value & mask);
        return true;
    case Edi:
        edi = (edi & ~mask) | (value & mask);
        return true;
    case Eip:
        eip = (eip & ~mask) | (value & mask);
        return true;
    case Ss:
        ss = (ss & ~mask) | (value & mask);
        return true;
    case Cs:
        cs = (cs & ~mask) | (value & mask);
        return true;
    case Ds:
        ds = (ds & ~mask) | (value & mask);
        return true;
    case Es:
        es = (es & ~mask) | (value & mask);
        return true;
    case Fs:
        fs = (fs & ~mask) | (value & mask);
        return true;
    case Gs:
        gs = (gs & ~mask) | (value & mask);
        return true;
    }
    throw std::runtime_error("set_register failed");
}

uint32_t
Registers::get_register_by_index(size_t index, Width w) {
    if (w == U8) {
        switch (index) {
        case 0b000:
            return eax & 0xff;
        case 0b001:
            return ecx & 0xff;
        case 0b010:
            return edx & 0xff;
        case 0b011:
            return ebx & 0xff;
        case 0b100:
            return (eax & 0xff00) >> 8;
        case 0b101:
            return (ecx & 0xff00) >> 8;
        case 0b110:
            return (edx & 0xff00) >> 8;
        case 0b111:
            return (ebx & 0xff00) >> 8;
        }
        throw std::runtime_error("get_register_by_index 8-bit must be general register");
    }
    uint32_t mask;
    switch (w) {
    case U16:
        mask = 0xffff;
        break;
    case U32:
        mask = 0xffffffff;
        break;
    }

    switch (index) {
    case 0b000:
        return eax & mask;
    case 0b001:
        return ecx & mask;
    case 0b010:
        return edx & mask;
    case 0b011:
        return ebx & mask;
    case 0b100:
        return esp & mask;
    case 0b101:
        return ebp & mask;
    case 0b110:
        return esi & mask;
    case 0b111:
        return edi & mask;
    }
    throw std::runtime_error("get_register_by_index reached end");
}

void
Registers::print_status_flags() {
    // XXX ugh
    printf("EFLAGS: af:%s,  \n", get_af() ? "1" : "0");
    printf("EFLAGS: cf:%s,  \n", get_cf() ? "1" : "0");
    printf("EFLAGS: df:0,  \n"); // XXX implement df, if, tf
    printf("EFLAGS: if:0,  \n");
    //printf("%d", get_df());
    //printf("%d", get_if());
    printf("EFLAGS: of:%s,  \n", get_of() ? "1" : "0");
    printf("EFLAGS: pf:%s,  \n", get_pf() ? "1" : "0");
    printf("EFLAGS: sf:%s,  \n", get_sf() ? "1" : "0");
    //printf("%d", get_tf());
    printf("EFLAGS: tf:0,  \n");
    printf("EFLAGS: zf:%s,  ", get_zf() ? "1" : "0");
    printf("\n");
}

void
Registers::update_status_flags(uint64_t a, uint64_t b, uint64_t c, Width w, bool flip_sign, bool no_af, bool zero_of_cf) {
    size_t size_bytes = width_to_size(w);

    bool sign_a = (a >> (size_bytes * 8 - 1)) & 1;
    bool sign_b = (b >> (size_bytes * 8 - 1)) & 1;
    bool sign_c = (c >> (size_bytes * 8 - 1)) & 1;
    printf("XXX: sign_a: %d, sign_b: %d, sign_c: %d\n", sign_a, sign_b, sign_c);

    if (!flip_sign) {
        set_of((sign_a == sign_b) & (sign_a != sign_c));
        set_cf(c > (((uint64_t)1 << (size_bytes * 8)) - 1));
        printf("XXX: c: %llu\n", c);
        printf("XXX: size_bytes: %d\n", size_bytes);
        printf("XXX: maxsize[w]: %llu\n", ((uint64_t)1 << (size_bytes * 8)) - 1);
        printf("XXX: c > maxsize[w]: %d\n", (c > (((uint64_t)1 << (size_bytes * 8)) - 1)));
        if (!no_af) {
            set_af(((a & 255) + (b & 255)) > 255);
        }
    } else {
        set_of((sign_a != sign_b) & (sign_a != sign_c));
        set_cf(b > a);
        if (!no_af) {
            set_af((b & 255) > (a & 255));
        }
    }

    // XXX ugh
    if (zero_of_cf) {
        set_of(0);
        set_cf(0);
    }

    set_sf(sign_c);
    set_zf(c == 0);

    uint8_t low8_parity = c & 255;
    low8_parity ^= low8_parity >> 4;
    low8_parity ^= low8_parity >> 2;
    low8_parity ^= low8_parity >> 1;
    set_pf((~low8_parity) & 1);
}

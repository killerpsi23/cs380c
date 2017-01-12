#include "icode.h"

#include <cstdio>

void print_cfg(Program *prog) {
	for (auto func: prog->funcs) {
		printf("Function: %lld\n", func->blocks.cbegin()->second->instr[0].addr);

		printf("Basic blocks:");
		for (auto iter : func->blocks)
			printf(" %lld", iter.second->instr[0].addr);

		printf("\nCFG:\n");
		for (auto iter : func->blocks) {
			Block* b = iter.second;
			printf("%lld ->", b->instr[0].addr);
			if (b->seq_next != nullptr)
				printf(" %lld", b->seq_next->instr[0].addr);
			if (b->br_next != nullptr)
				printf(" %lld", b->br_next->instr[0].addr);
			putchar('\n');
		}
	}
}


int main() {
    Program prog(fopen("debug.txt", "r"));

    prog.find_functions();
    prog.build_domtree();
    prog.compute_df();
    prog.find_defs();
    prog.place_phi();
    prog.ssa_rename_var();

    prog.ssa_licm();
    print_cfg(&prog);

    prog.remove_phi();
    prog.icode(stdout);

    //prog.ssa_constant_propagate();

    //prog.icode(stdout);

    //    printf("Basic blocks:");
    //    for (auto iter : func->blocks)
    //        printf(" %lld", iter.second->addr());

    //    printf("\nCFG:\n");
    //    for (auto iter : func->blocks) {
    //        Block* b = iter.second;
    //        printf("%lld ->", b->addr());
    //        if (b->seq_next != nullptr)
    //            printf(" %lld", b->seq_next->addr());
    //        if (b->br_next != nullptr)
    //            printf(" %lld", b->br_next->addr());
    //        putchar('\n');
    //    }

    //    printf("\nDom Tree:\n");
    //    for (auto iter : func->blocks) {
    //        Block* b = iter.second;
    //        printf("%lld ->", b->addr());
    //        for (Block *c: b->domc)
    //            printf(" %lld", c->addr());
    //        putchar('\n');
    //    }

    //    printf("\nDF:\n");
    //    for (auto iter : func->blocks) {
    //        Block *b = iter.second;
    //        printf("%lld :", b->addr());
    //        for (Block *df: b->df)
    //            printf(" %lld", df->addr());
    //        putchar('\n');
    //    }

    //    printf("\nPhi:\n");
    //    for (auto iter : func->blocks) {
    //        Block *b = iter.second;
    //        printf("%lld :\n", b->addr());
    //        for (const auto& var_phi : b->phi) {
    //            const std::string& var = var_phi.first;
    //            const Phi& phi = var_phi.second;

    //            printf("  [%s] %d <-", var.c_str(), phi.l);
    //            for (int idx : phi.r)
    //                printf(" %d", idx);
    //            putchar('\n');
    //        }
    //        putchar('\n');
    //    }
    //}

    return 0;
}

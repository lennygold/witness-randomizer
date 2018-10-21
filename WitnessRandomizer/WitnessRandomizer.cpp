#include "pch.h"
#include "Memory.h"
#include <string>

void SwapPanelTargets(Memory memory, int panel1, int panel2) {
	std::vector<int> panel1Offset = {0x5B28C0, 0x18, panel1*8, 0x2BC};
	std::vector<int> panel2Offset = {0x5B28C0, 0x18, panel2*8, 0x2BC};
	// Currently wired for old version
	int panel1Target = memory.ReadData<int>(panel1Offset, 1)[0];
	int panel2Target = memory.ReadData<int>(panel2Offset, 1)[0];

	memory.WriteData<int>(panel1Offset, {panel2Target});
	memory.WriteData<int>(panel2Offset, {panel1Target});
}

void RandomizePanels(Memory memory, std::vector<int> panels) {
	for (int i=panels.size() - 1; i > 1; i--) {
		int target = rand() % i;
		if (i != target) {
			SwapPanelTargets(memory, panels[i], panels[target]);
			std::swap(panels[i], panels[target]);
		}
	}
}

int main(char** argv, int argc)
{
	if (argc == 2) {
		srand(atoi(argv[1])); // Seed with RNG from command line
	}
	Memory memory = Memory("witness64_d3d11.exe");

	std::vector<int> tutorialPanels = {
		// 0x0A3B5, // Back Left
		0x0A3B2, // Back Right
		0x00295, // Center Left
		0x00293, // Front Center
		0x002C2, // Front Left
		0x0C335, // Pillar
	};

	RandomizePanels(memory, tutorialPanels);
}
